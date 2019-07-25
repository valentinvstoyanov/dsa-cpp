#include <iostream>
#include "floyd_warshall.h"

int main() {
  Graph<int, int, true> g(1, 5);
  g.AddEdge(1,2,6);
  g.AddEdge(1,3,8);
  g.AddEdge(1,5,-4);
  g.AddEdge(2,4,1);
  g.AddEdge(2,5,7);
  g.AddEdge(3,2,4);
  g.AddEdge(4,3,-5);
  g.AddEdge(4,1,2);
  g.AddEdge(5,4,3);

  std::unordered_map<int, std::unordered_map<int,int>> dist = FloydWarshall(g);
  for (const auto& x: dist) {
    for (const auto& y: x.second) {
      printf("From %d to %d is %d\n", x.first, y.first, y.second);
    }
  }

  return 0;
}