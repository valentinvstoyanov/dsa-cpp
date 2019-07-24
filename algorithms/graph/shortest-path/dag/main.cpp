#include <iostream>
#include "ssshp_dag.h"

int main() {
  Graph<int, int, true> g;
  for (int i = 0; i < 6; ++i) g.AddVertex(i);
  g.AddEdge(0, 1, 5);
  g.AddEdge(0, 2, 3);
  g.AddEdge(1, 3, 6);
  g.AddEdge(1, 2, 2);
  g.AddEdge(2, 4, 4);
  g.AddEdge(2, 5, 2);
  g.AddEdge(2, 3, 7);
  g.AddEdge(3, 4, -1);
  g.AddEdge(4, 5, -2);

  const auto pair = SSShPDag(g, 1);
  std::unordered_map<int, int> parent = pair.first;
  std::unordered_map<int, int> dist = pair.second;

  for (const auto& d: dist) {
    printf("1 ~~%d~~> %d\n", d.second, d.first);
  }
  return 0;
}