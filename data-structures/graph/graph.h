#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <queue>
#include <cassert>

template<typename V = int, typename E = int, bool directed = false>
class Graph {
 public:
  using EdgeMap = std::unordered_map<V, E>;
  using VertexMap = std::unordered_map<V, EdgeMap>;
  using VisitCallback = std::function<bool(const V&)>;
 private:
  VertexMap vertex_map_;
  size_t edge_count_;

  VertexMap TransposeVertexMap() const {
    VertexMap transposed_vertex_map;

    for (const auto& vit: vertex_map_) {
      transposed_vertex_map.insert(std::make_pair(vit.first, EdgeMap()));

      for (const auto& eit: vit.second)
        transposed_vertex_map[eit.first][vit.first] = eit.second;
    }

    return transposed_vertex_map;
  }

 public:
  bool AddVertex(const V& vertex) {
    if (vertex_map_.find(vertex) == vertex_map_.end()) {
      vertex_map_.insert(std::make_pair(vertex, EdgeMap()));
      return true;
    }

    return false;
  }

  bool AddEdge(const V& from, const V& to, const E& edge = 1) {
    auto from_it = vertex_map_.find(from);
    auto to_it = vertex_map_.find(to);
    if (from_it == vertex_map_.end() || to_it == vertex_map_.end())
      return false;

    if (!directed)
      to_it->second[from] = edge;

    from_it->second[to] = edge;
    ++edge_count_;

    return true;
  }

  bool RemoveVertex(const V& vertex) {
    auto vertex_it = vertex_map_.find(vertex);
    if (vertex_it == vertex_map_.end())
      return false;

    const size_t adjacent_count = vertex_it->second.size();
    vertex_map_.erase(vertex_it);

    for (auto& element: vertex_map_) {
      EdgeMap& adjacent = element.second;
      auto edge_it = adjacent.find(element.first);
      if (edge_it != adjacent.end()) {
        adjacent.erase(edge_it);
        --edge_count_;
      }
    }

    return true;
  }

  bool RemoveEdge(const V& from, const V& to) {
    auto from_it = vertex_map_.find(from);
    auto to_it = vertex_map_.find(to);
    if (from_it == vertex_map_.end() || to_it == vertex_map_.end())
      return false;

    if ((!directed && from_it->second.erase(to) != 0 && to_it->second.erase(from) != 0) || from_it->second.erase(to) != 0) {
      --edge_count_;
      return true;
    }

    return false;
  }

  bool BFSVisit(const V& start, const VisitCallback& visit, std::unordered_set<V>& visited) const {
    std::queue<V> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
      const V current = q.front();
      q.pop();

      if (!visit(current))
        return true;

      const EdgeMap& adj = vertex_map_.find(current)->second;
      for (const auto& element: adj) {
        const V& vertex = element.first;

        if (visited.find(vertex) == visited.end()) {
          q.push(vertex);
          visited.insert(vertex);
        }
      }
    }

    return true;
  }

  bool DFSVisit(const V& start, const VisitCallback& visit, std::unordered_set<V>& visited) const {
    if (visited.find(start) != visited.end())
      return true;

    visited.insert(start);
    if (!visit(start))
      return false;

    const EdgeMap& adj = vertex_map_.find(start)->second;
    for (const auto& element: adj) {
      const V& vertex = element.first;

      if (visited.find(vertex) == visited.end())
        if (!DFSVisit(vertex, visit, visited))
          return false;
    }

    return true;
  }

  void BFS(const VisitCallback& visit) const {
    std::unordered_set<V> visited;

    for (const auto& vit: vertex_map_)
      if (visited.find(vit.first) == visited.end())
        if (!BFSVisit(vit.first, visit, visited))
          return;
  }

  bool BFSVisit(const V& start, const VisitCallback& visit) const {
    if (vertex_map_.find(start) == vertex_map_.end())
      return false;

    std::unordered_set<V> visited;
    BFSVisit(start, visit, visited);

    return true;
  }

  void DFS(const VisitCallback& visit) const {
    std::unordered_set<V> visited;

    for (const auto& vit: vertex_map_)
      if (visited.find(vit.first) == visited.end())
        if (!DFSVisit(vit.first, visit, visited))
          return;
  }

  bool DFSVisit(const V& start, const VisitCallback& visit) const {
    if (vertex_map_.find(start) == vertex_map_.end())
      return false;

    std::unordered_set<V> visited;
    DFSVisit(start, visit, visited);

    return true;
  }

  std::unordered_map<V, unsigned> OutDegrees() const {
    assert(directed && "Cannot retrieve out-degrees from undirected graph.");
    std::unordered_map<V, unsigned> out_degree_map;

    for (const auto& vit: vertex_map_)
        out_degree_map[vit.first] = vit.second.size();

    return out_degree_map;
  }

  std::unordered_map<V, unsigned> InDegrees() const {
    assert(directed && "Cannot retrieve in-degrees from undirected graph.");
    std::unordered_map<V, unsigned> in_degree_map;

    for (const auto& vit: vertex_map_)
      in_degree_map[vit.first] = 0;

    for (const auto& vit: vertex_map_)
      for (const auto& eit: vit.second)
        ++in_degree_map[eit.first];


    return in_degree_map;
  }

  std::vector<V> Sinks() const {
    assert(directed && "Cannot retrieve sinks from undirected graph.");
    std::unordered_map<V, unsigned> in_degree_map = InDegrees();

    std::vector<V> result;
    for (const auto& pair: in_degree_map)
      if (pair.second == 0)
        result.push_back(pair.first);

    return result;
  }

  std::vector<V> Sources() const {
    assert(directed && "Cannot retrieve sources from undirected graph.");
    std::vector<V> result;

    for (const auto& vit: vertex_map_)
      if (vit.second.empty())
        result.push_back(vit.first);

    return result;
  }

  Graph Transpose() const {
    Graph<V, E, directed> transposed_graph;
    transposed_graph.vertex_map_ = TransposeVertexMap();
    transposed_graph.edge_count_ = edge_count_;
    return transposed_graph;
  }

  const VertexMap& AdjacencyList() const {
    return vertex_map_;
  }

  const EdgeMap& Adj(const V& vertex) const {
    auto it = vertex_map_.find(vertex);
    assert(it != vertex_map_.end() && "Adj called with non-existing vertex.");
    return it->second;
  }

  size_t VertexCount() const {
    return vertex_map_.size();
  }

  size_t EdgeCount() const {
    return edge_count_;
  }

  bool IsDirected() const {
    return directed;
  }

  bool IsUndirected() const {
    return !directed;
  }

  std::string AsAdjacencyListString() const {
    std::string result;

    for (const auto& vit: vertex_map_) {
      result += std::to_string(vit.first);
      result += ": ";

      for (const auto& eit: vit.second) {
        result += "(";
        result += std::to_string(eit.first);
        result += ", ";
        result += std::to_string(eit.second);
        result += "), ";
      }

      result = result.substr(0, result.length() - 2);
      result += '\n';
    }

    return result;
  }
};

#endif //GRAPH_GRAPH_H
