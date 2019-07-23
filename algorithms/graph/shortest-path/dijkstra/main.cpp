#include <iostream>
#include "dijkstra.h"

int main() {
  Graph<int, int, false> g;
  for (int i = 0; i < 9; ++i) g.AddVertex(i);
  g.AddEdge(0, 1, 4);
  g.AddEdge(0, 7, 8);
  g.AddEdge(1, 2, 8);
  g.AddEdge(1, 7, 11);
  g.AddEdge(2, 3, 7);
  g.AddEdge(2, 8, 2);
  g.AddEdge(2, 5, 4);
  g.AddEdge(3, 5, 14);
  g.AddEdge(3, 4, 9);
  g.AddEdge(4, 5, 10);
  g.AddEdge(5, 6, 2);
  g.AddEdge(6, 7, 1);
  g.AddEdge(6, 8, 6);
  g.AddEdge(7, 8, 7);

  const auto pair = Dijkstra(g, 0);
  std::unordered_map<int, int> parent = pair.first;
  std::unordered_map<int, int> dist = pair.second;

  printf("%d\n", parent[8]);

  for (const auto& d: dist) {
    printf("0 --%d--> %d\n", d.second, d.first);
  }

  return 0;
}