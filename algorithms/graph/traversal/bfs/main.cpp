#include <iostream>
#include "bfs.h"

int main() {
  Graph<int, int, false> g;

  for (int i = 0; i < 4; ++i)
    g.AddVertex(i);

  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(1, 2);
  g.AddEdge(2, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 3);


  const auto cb = [](const int& x, Color color) -> void {
    if (color == WHITE) printf("%d ", x);
  };

  BFS<int, int, false>(g, 2, cb); printf("\n");

  return 0;
}