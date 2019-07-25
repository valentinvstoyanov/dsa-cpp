#ifndef FLOYD_WARSHALL_FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_FLOYD_WARSHALL_H

#include "../../../../data-structures/graph/graph.h"

template<typename V, typename E, bool directed>
std::unordered_map<V, std::unordered_map<V, E>> FloydWarshall(const Graph<V, E, directed>& graph) {
  const auto inf = std::numeric_limits<E>::max();
  std::unordered_map<V, std::unordered_map<V, E>> dist;
  for (const auto& x: graph.AdjacencyList())
    for (const auto& y: graph.AdjacencyList())
      dist[x.first][y.first] = inf;
  for (const auto& x: graph.AdjacencyList()) {
    for (const auto& y: x.second)
      dist[x.first][y.first] = y.second;
    dist[x.first][x.first] = 0;
  }

  for (const auto& k: graph.AdjacencyList())
    for (const auto& x: graph.AdjacencyList())
      for (const auto& y: x.second) {
        const auto& d1 = dist[x.first][k.first];
        const auto& d2 = dist[k.first][y.first];
        if (d1 == inf || d2 == inf) continue;

        E new_dist = d1 + d2;
        if (dist[x.first][y.first] > new_dist) {
          dist[x.first][y.first] = new_dist;
        }
      }

  return dist;
}

#endif //FLOYD_WARSHALL_FLOYD_WARSHALL_H
