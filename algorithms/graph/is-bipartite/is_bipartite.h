#ifndef IS_BIPARTITE_IS_BIPARTITE_H
#define IS_BIPARTITE_IS_BIPARTITE_H

#include "../traversal/bfs/bfs.h"

template <typename V, typename E, bool directed>
bool IsBipartite(const Graph<V, E, directed>& graph) {
  bool result = true;
  BFS<V, E, directed>(graph, [&result](const V& x, Color color) {
    if (color == GRAY) result = false;
  });

  return result;
}

#endif //IS_BIPARTITE_IS_BIPARTITE_H
