#include <iostream>
#include "kruskal.h"

int main() {
  Graph<char, int, false> graph;
  for (char c = 'a'; c <= 'f'; ++c)
    graph.AddVertex(c);

  graph.AddEdge('a', 'b', 4);
  graph.AddEdge('a', 'f', 2);
  graph.AddEdge('b', 'c', 6);
  graph.AddEdge('b', 'f', 3);
  graph.AddEdge('c', 'f', 1);
  graph.AddEdge('c', 'd', 3);
  graph.AddEdge('f', 'e', 4);
  graph.AddEdge('e', 'd', 2);

  const auto& resultp = MSTKruskal(graph, 'a');
  const auto& result = resultp.first;
  printf("Weight: %d\n", resultp.second);
  for (const auto& edge: result)
    std::cout << '(' << edge.to << ", " << edge.from << ")\n";

  printf("\n");

  Graph<int, int, false> graph1;
  for (int c = 1; c <= 6; ++c)
    graph1.AddVertex(c);

  graph1.AddEdge(1, 2, 1);
  graph1.AddEdge(1, 3, 9);
  graph1.AddEdge(1, 6, 14);
  graph1.AddEdge(2, 3, 10);
  graph1.AddEdge(2, 4, 15);
  graph1.AddEdge(3, 6, 2);
  graph1.AddEdge(3, 4, 11);
  graph1.AddEdge(4, 5, 6);
  graph1.AddEdge(5, 6, 9);

  const auto& result1p = MSTKruskal(graph1, 1);
  const auto& result1 = result1p.first;
  printf("Weight: %d\n", result1p.second);
  for (const auto& edge: result1)
    std::cout << '(' << edge.from << ", " << edge.to << ")\n";

  return 0;
}