#ifndef PRIM_PRIM_H
#define PRIM_PRIM_H

#include <limits>
#include "../../../../data-structures/graph/graph.h"
#include "../../../../data-structures/binary-heap/binary_heap.h"

template<typename V, typename E>
std::pair<std::unordered_map<V, V>, E> MSTPrim(const Graph<V, E, false>& graph, const V& start) {
  struct Compare {
    bool operator()(const std::pair<V, E>& p1, const std::pair<V, E>& p2) const {
      return p1.second > p2.second;
    }
  };

  const auto inf = std::numeric_limits<E>::max();
  std::unordered_map<V, E> weight;
  std::unordered_set<V> visited;
  std::unordered_map<V, V> parent;
  std::priority_queue<std::pair<V, E>, std::vector<std::pair<V, E>>, Compare> pq;

  for (const auto& pair: graph.AdjacencyList())
    weight[pair.first] = inf;
  weight[start] = 0;

  pq.push(std::make_pair(start, 0));

  for (int i = 1; i < graph.VertexCount(); ++i) {
    std::pair<V, E> x = pq.top();
    pq.pop();
    visited.insert(x.first);

    for (const std::pair<V, E>& y: graph.Adj(x.first)) {
      if (visited.find(y.first) == visited.end()) {
        if (y.second < weight[y.first]) {
          weight[y.first] = y.second;
          parent[y.first] = x.first;
          pq.push(std::make_pair(y.first, weight[y.first]));
        }
      }
    }
  }

  E sum(0);
  for (const auto& pair: weight)
    sum += pair.second;

  return std::make_pair(parent, sum);
}

#endif //PRIM_PRIM_H
