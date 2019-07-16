#ifndef BFS_BFS_H
#define BFS_BFS_H

#include "../../../../data-structures/graph/graph.h"
#include "../../../../data-structures/queue/queue-using-linked-list/queue.h"

template<typename V, typename E>
struct BFSData {
 public:
  V* predecessor;
  E dist;
  Color color;

  explicit BFSData(V* pred = nullptr, const E& dist = std::numeric_limits<E>::max(), Color col = WHITE)
      : predecessor(pred), dist(dist), color(col) {}
};

template<typename V, typename E>
using BFSDataMap = std::unordered_map<V, BFSData<V, E>>;

template<typename V, typename E, bool directed>
BFSDataMap<V, E> InitBFSDataMap(const Graph<V, E, directed>& g) {
  BFSDataMap<V, E> data;
  for (const auto& vit: g.AdjacencyList())
    data[vit.first] = BFSData<V, E>();
  return data;
}

template<typename V>
using BFSCallback = std::function<void(const V&, Color)>;

template<typename V, typename E, bool directed>
BFSDataMap<V, E> BFS(const Graph<V, E, directed>& graph, const V& start, const BFSCallback<V>& callback, BFSDataMap<V, E>& data) {
  Queue<V> queue;
  queue.Enqueue(start);
  if (callback) callback(start, WHITE);
  data[start].color = Color::GRAY;
  data[start].dist = E(0);

  while (!queue.Empty()) {
    V x = queue.Dequeue();

    for (const auto adj: graph.Adj(x)) {
      const V& y = adj.first;
      BFSData<V, E>& data_y = data[y];
      if (callback) callback(y, data_y.color);

      if (data_y.color == Color::WHITE) {
        data_y.color = Color::GRAY;
        data_y.dist = data[x].dist + E(1);
        data_y.predecessor = &x;
        queue.Enqueue(y);
      }
    }

    data[x].color = Color::BLACK;
  }

  return data;
}

template<typename V, typename E, bool directed>
BFSDataMap<V, E> BFS(const Graph<V, E, directed>& graph, const V& start, const BFSCallback<V>& callback = nullptr) {
  auto data = InitBFSDataMap(graph);
  return BFS(graph, start, callback, data);
}

template<typename V, typename E, bool directed>
BFSDataMap<V, E> BFS(const Graph<V, E, directed>& graph, const BFSCallback<V>& callback = nullptr) {
  BFSDataMap<V, E> data = InitBFSDataMap(graph);
  for (const std::pair<V, BFSData<V, E>>& pair: data)
    if (pair.second.color == WHITE)
      BFS(graph, pair.first, callback, data);

  return data;
}

#endif //BFS_BFS_H
