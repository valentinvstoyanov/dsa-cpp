#ifndef CONNECTED_COMPONENTS_CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_CONNECTED_COMPONENTS_H

#include "../traversal/bfs/bfs.h"

template<typename V, typename E>
std::vector<std::vector<V>> ConnectedComponents(const Graph<V, E, false>& graph) {
  std::vector<std::vector<V>> result;
  std::vector<V> temp;
  auto callback = [&temp](const V& x, Color color) { if (color == WHITE) temp.push_back(x); };
  auto data = InitBFSDataMap(graph);

  for (const auto& pair: data) {
    if (pair.second.color == WHITE) {
      BFS<V, E, false>(graph, pair.first, callback, data);
      result.push_back(temp);
      temp.clear();
    }
  }

  return result;
}

template<typename V, typename E>
int CountConnectedComponents(const Graph<V, E, false>& graph) {
  int counter = 0;
  auto data = InitBFSDataMap(graph);

  for (const auto& pair: data) {
    if (pair.second.color == WHITE) {
      ++counter;
      BFS<V, E, false>(graph, pair.first, nullptr, data);
    }
  }

  return counter;
}

#endif //CONNECTED_COMPONENTS_CONNECTED_COMPONENTS_H
