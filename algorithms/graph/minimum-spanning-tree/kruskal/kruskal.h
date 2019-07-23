#ifndef KRUSKAL_KRUSKAL_H
#define KRUSKAL_KRUSKAL_H

#include <unordered_map>
#include <algorithm>
#include "../../../../data-structures/graph/graph.h"
#include "../../../../data-structures/disjoint-set/disjoint_set.h"

template<typename V, typename E>
struct Edge {
  V from;
  V to;
  E weight;

  bool operator<(const Edge& edge) const {
    return weight < edge.weight;
  }
};

template<typename V, typename E>
std::pair<std::vector<Edge<V, E>>, E> MSTKruskal(const Graph<V, E, false>& graph, const V& start) {
  std::vector<V> vertices;
  std::vector<Edge<V, E>> edges;
  for (const auto& vit: graph.AdjacencyList()) {
    vertices.push_back(vit.first);
    for (const auto& eit: vit.second)
      edges.push_back(Edge<V, E>{vit.first, eit.first, eit.second});
  }

  std::sort(edges.begin(), edges.end());

  std::unordered_map<V, size_t> mapping = DisjointSet::DefaultMapping(vertices);
  DisjointSet disjoint_set(vertices.size());
  E sum(0);
  std::vector<Edge<V, E>> result;

  for (const Edge<V, E>& edge: edges) {
    const auto mapped_from = mapping[edge.from];
    const auto mapped_to = mapping[edge.to];

    if (!disjoint_set.SameSet(mapped_from, mapped_to)) {
      result.push_back(edge);
      sum += edge.weight;
      disjoint_set.Union(mapped_from, mapped_to);
    }
  }

  return std::make_pair(result, sum);
}

#endif //KRUSKAL_KRUSKAL_H
