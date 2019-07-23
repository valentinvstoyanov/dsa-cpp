#ifndef DIJKSTRA_DIJKSTRA_H
#define DIJKSTRA_DIJKSTRA_H

#include <utility>
#include <unordered_map>
#include "../../../../data-structures/graph/graph.h"

template <typename V, typename E, bool directed>
std::pair<std::unordered_map<V, V>, std::unordered_map<V, E>> Dijkstra(const Graph<V, E, directed>& graph, const V& start) {
  const auto inf = std::numeric_limits<E>::max();
  struct Compare {
    bool operator()(const std::pair<V, E>& p1, const std::pair<V, E>& p2) const {
      return p1.second > p2.second;
    }
  };
  std::priority_queue<std::pair<V, E>, std::vector<std::pair<V, E>>, Compare> pq;
  std::unordered_set<V> visited;
  std::unordered_map<V, V> parent;
  std::unordered_map<V, E> dist;
  for (const auto& pair: graph.AdjacencyList()) {
    parent[pair.first] = V(-1);
    dist[pair.first] = inf;
  }
  dist[start] = E(0);
  pq.push(std::make_pair(start, E(0)));
  
  while (!pq.empty()) {
    std::pair<V, E> x = pq.top();
    pq.pop();
    visited.insert(x.first);

    for (const std::pair<V, E>& y: graph.Adj(x.first)) {
      E new_dist = y.second + dist[x.first];
      if (new_dist < dist[y.first] && visited.find(y.first) == visited.end()) {
        dist[y.first] = new_dist;
        parent[y.first] = x.first;
        pq.push(std::make_pair(y.first, new_dist));
      }
    }
  }

  return std::make_pair(parent, dist);
}

#endif //DIJKSTRA_DIJKSTRA_H
