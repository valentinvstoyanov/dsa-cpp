#include <iostream>
#include "connected_components.h"

int main() {
  Graph<int, int, false> g;
  for (int i = 0; i < 5; ++i) g.AddVertex(i);

  g.AddEdge(1, 0);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);

  printf("CC count: %d\n", CountConnectedComponents(g));

  std::vector<std::vector<int>> cc = ConnectedComponents(g);
  for (const auto& vect: cc) {
    for (const auto& vert: vect) {
      printf("%d ", vert);
    }
    printf("\n");
  }

  return 0;
}