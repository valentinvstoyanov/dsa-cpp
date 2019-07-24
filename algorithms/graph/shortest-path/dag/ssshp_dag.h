#ifndef DAG_SSSHP_DAG_H
#define DAG_SSSHP_DAG_H

#include "../../topo-sorting/topo_sorting.h"

template<typename V, typename E>
std::pair<std::unordered_map<V, V>, std::unordered_map<V, E>> SSShPDag(const Graph<V, E, true>& graph, const V& start) {
  const auto inf = std::numeric_limits<E>::max();
  std::vector<V> topo_order = TopoSort(graph);
  std::unordered_map<V, V> parent;
  std::unordered_map<V, E> dist;
  for (const V& v: topo_order) {
    parent[v] = V(-1);
    dist[v] = inf;
  }
  dist[start] = 0;

  for (const V& x: topo_order) {
    if (dist[x] == inf)
      continue;
    for (const auto& neighbour: graph.Adj(x)) {
      E new_dist = dist[x] + neighbour.second;
      if (new_dist < dist[neighbour.first]) {
        dist[neighbour.first] = new_dist;
        parent[neighbour.first] = x;
      }
    }
  }

  return std::make_pair(parent, dist);
}

#endif //DAG_SSSHP_DAG_H
