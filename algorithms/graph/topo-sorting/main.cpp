#include <iostream>
#include "topo_sorting.h"

int main() {
  Graph<int, int, true> graph;

  for (int i = 0; i <= 5; ++i)
    graph.AddVertex(i);
  graph.AddEdge(5, 2);
  graph.AddEdge(5, 0);
  graph.AddEdge(4, 0);
  graph.AddEdge(4, 1);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 1);

  std::cout << graph.AsAdjacencyListString() << "\n\n";

  const std::vector<int> topo_order = TopoSort(graph);

  for (const auto& element: topo_order)
    std::cout << element << " ";
  std::cout << std::endl;

  return 0;
}