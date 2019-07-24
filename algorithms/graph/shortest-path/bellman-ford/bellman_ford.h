#ifndef BELLMAN_FORD_BELLMAN_FORD_H
#define BELLMAN_FORD_BELLMAN_FORD_H

#include <unordered_map>
#include <limits>
#include "../../../../data-structures/graph/graph.h"

template <typename V, typename E, bool directed>
std::pair<std::unordered_map<V, V>, std::unordered_map<V, E>> BellmanFord(const Graph<V, E, directed>& graph, const V& start) {
  const auto inf = std::numeric_limits<E>::max();
  std::unordered_map<V, E> dist;
  std::unordered_map<V, V> parent;
  for(const auto& vit: graph.AdjacencyList()) {
    dist[vit.first] = inf;
    parent[vit.first] = V(-1);
  }
  dist[start] = E(0);

  for (int i = 2; i < graph.VertexCount(); ++i) {
    for(const auto& x: graph.AdjacencyList()) {
      for(const auto& y: x.second) {
        E new_dist = dist[x.first] == inf ? inf : dist[x.first] + y.second;
        if (new_dist < dist[y.first]) {
          dist[y.first] = new_dist;
          parent[y.first] = x.first;
        }
      }
    }
  }

  for(const auto& x: graph.AdjacencyList())
    for(const auto& y: x.second)
      if (dist[x.first] + y.second < dist[y.first])
        throw std::runtime_error("Negative cycle detected.");

  return std::make_pair(parent, dist);
}

#endif //BELLMAN_FORD_BELLMAN_FORD_H
