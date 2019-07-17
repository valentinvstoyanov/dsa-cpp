#ifndef DFS_DFS_H
#define DFS_DFS_H

#include "../../../../data-structures/graph/graph.h"

template<typename V>
struct DFSData {
  V predecessor;
  Color color;
  unsigned discovery_time;
  unsigned finalization_time;

  explicit DFSData(V pred = V(-1),
                   Color col = WHITE,
                   unsigned discovery_time = 0,
                   unsigned finalization_time = 0)
      : predecessor(pred),
        color(col),
        discovery_time(discovery_time),
        finalization_time(finalization_time) {}
};

template<typename V>
using DFSDataMap = std::unordered_map<V, DFSData<V>>;

template<typename V, typename E, bool directed>
DFSDataMap<V> InitDFSDataMap(const Graph<V, E, directed>& g) {
  DFSDataMap<V> data;
  for (const auto& vit: g.AdjacencyList())
    data[vit.first] = DFSData<V>();
  return data;
}

template<typename V>
using DFSCallback = std::function<void(const V&, Color)>;

template<typename V, typename E, bool directed>
DFSDataMap<V> DFS(const Graph<V, E, directed>& graph,
                  const V& start,
                  const DFSCallback<V>& callback,
                  DFSDataMap<V>& data,
                  unsigned& time) {
  DFSData<V>& data_start = data[start];
  if (callback && data_start.predecessor == V(-1)) callback(start, data_start.color);
  if (data_start.color != WHITE)
    return data;

  data_start.discovery_time = ++time;
  data_start.color = GRAY;

  for (const std::pair<V, E>& pair: graph.Adj(start)) {
    const V& x = pair.first;

    DFSData<V>& data_x = data[x];
    if (callback) callback(x, data_x.color);
    if (data_x.color == WHITE) {
      data_x.predecessor = start;
      DFS(graph, x, callback, data);
    }
  }

  data_start.color = BLACK;
  data_start.finalization_time = ++time;
  return data;
}

template<typename V, typename E, bool directed>
DFSDataMap<V> DFS(const Graph<V, E, directed>& graph,
                  const V& start,
                  const DFSCallback<V>& callback,
                  DFSDataMap<V>& data) {
  unsigned time = 0;
  return DFS<V, E, directed>(graph, start, callback, data, time);
}

template<typename V, typename E, bool directed>
DFSDataMap<V> DFS(const Graph<V, E, directed>& graph, const V& start, const DFSCallback<V>& callback = nullptr) {
  DFSDataMap<V> data = InitDFSDataMap(graph);
  return DFS<V, E, directed>(graph, start, callback, data);
}

template<typename V, typename E, bool directed>
DFSDataMap<V> DFS(const Graph<V, E, directed>& graph, const DFSCallback<V>& callback = nullptr) {
  auto data = InitDFSDataMap(graph);
  unsigned time = 0;

  for (const auto& pair: data)
    if (pair.second.color == WHITE)
      DFS(graph, pair.first, callback, data, time);

  return data;
}

#endif //DFS_DFS_H
