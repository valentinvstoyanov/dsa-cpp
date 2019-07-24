#include <iostream>
#include "bellman_ford.h"

int main() {
  Graph<char, int, true> g;
  for (char c = 'A'; c <= 'E'; ++c) g.AddVertex(c);
  g.AddEdge('A', 'B', -1);
  g.AddEdge('A', 'C', 4);
  g.AddEdge('B', 'C', 3);
  g.AddEdge('B', 'D', 2);
  g.AddEdge('B', 'E', 2);
  g.AddEdge('D', 'B', 1);
  g.AddEdge('D', 'C', 5);
  g.AddEdge('E', 'D', -3);
  //For negative cycle: g.AddEdge('D', 'A', -3);
  const auto pair = BellmanFord(g, 'A');

  std::unordered_map<char, char> parent = pair.first;
  std::unordered_map<char, int> dist = pair.second;

  for (const auto& d: dist) {
    printf("A ~~%d~~> %c\n", d.second, d.first);
  }

  return 0;
}