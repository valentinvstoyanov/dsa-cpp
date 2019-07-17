#include <iostream>
#include "dfs.h"

int main() {
  Graph<int, int, true> g;
  for (int i = 0; i < 7; ++i) g.AddVertex(i);
  g.AddEdge(0, 1);
  g.AddEdge(0, 2);
  g.AddEdge(0, 5);
  g.AddEdge(0, 6);
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);
  g.AddEdge(4, 5);
  g.AddEdge(5, 1);

  auto cb =  [](const int& x, Color color) {
    if (color == WHITE) printf("%d ", x);
  };

  DFS<int, int, true>(g, 0, cb); printf("\n");

  g.AddVertex(100);
  DFS<int, int, true>(g, cb);

  return 0;
}