#include <iostream>
#include "is_bipartite.h"

int main() {
  Graph<int, int> g;
  for (int i = 0; i < 5; ++i) g.AddVertex(i);
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);

  printf("%d\n", IsBipartite(g));

  g.AddEdge(0, 2);
  printf("%d\n", IsBipartite(g));

  return 0;
}