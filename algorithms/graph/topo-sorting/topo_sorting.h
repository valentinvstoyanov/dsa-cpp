//
// Created by valentinvstoyanov on 07.05.19.
//

#ifndef TOPO_SORTING_TOPO_SORTING_H
#define TOPO_SORTING_TOPO_SORTING_H

#include "../../../data-structures/graph/graph.h"

template<typename V, typename E>
std::vector<V> TopoSort(const Graph<V, E, true>& graph) {
  std::unordered_map<V, unsigned> in_degrees = graph.InDegrees();

  std::queue<V> q;
  for (const auto& pair: in_degrees)
    if (pair.second == 0)
      q.push(pair.first);

  std::vector<V> result;
  while (!q.empty()) {
    const V current = q.front();
    q.pop();
    result.push_back(current);
    const auto& adj = graph.Adj(current);

    for (const auto& pair: adj)
      if (--in_degrees[pair.first] == 0)
        q.push(pair.first);
  }

  assert(result.size() == graph.VertexCount() && "Topological sorting cannot be performed due to cycle in the graph.");
  return result;
}

#endif //TOPO_SORTING_TOPO_SORTING_H
