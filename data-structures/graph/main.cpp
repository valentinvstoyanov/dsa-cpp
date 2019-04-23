#include <iostream>
#include "graph.h"

int main() {
  Graph<int, int> graph;
  const int size = 20;

  for (int i = 0; i < size; ++i) {
    bool res = graph.AddVertex(i);
    std::cout << "adding vertex " << i << " " << (res ? "succeeded." : "failed...") << std::endl;
  }

  int v = -1, u = -1;
  for (int i = 0; i < 100; ++i) {
    v = rand() % (size - 1);
    u = rand() % (size - 1);
    bool res = graph.AddEdge(v, u, i);
    std::cout << "adding edge from " << v << " to " << u << " " << (res ? "succeeded." : "failed...") << std::endl;
  }

  std::cout << "removing vertex 1 " << (graph.RemoveVertex(1) ? "succeeded." : "failed...") << std::endl;
  std::cout << "removing vertex 1 " << (graph.RemoveVertex(1) ? "succeeded." : "failed...") << std::endl;

  std::cout << "removing edge (" << v << ", " << u << ") " << (graph.RemoveEdge(v, u) ? "succeeded." : "failed...") << std::endl;
  std::cout << "removing edge (" << v << ", " << u << ") " << (graph.RemoveEdge(v, u) ? "succeeded." : "failed...") << std::endl;

  graph = Graph<int, int>();
  graph.AddVertex(1);
  graph.AddVertex(2);
  graph.AddVertex(3);
  graph.AddVertex(4);
  graph.AddVertex(5);
  graph.AddVertex(6);
  graph.AddVertex(7);

  graph.AddEdge(1, 2, 1);
  graph.AddEdge(1, 3, 1);

  graph.AddEdge(2, 4, 1);
  graph.AddEdge(2, 5, 1);

  graph.AddEdge(3, 6, 1);

  graph.AddEdge(4, 7, 1);
  graph.AddEdge(5, 7, 1);

  graph.AddEdge(6, 5, 1);
  graph.AddEdge(6, 7, 1);

  std::cout << graph.asAdjListString() << std::endl;

  graph.BFS([](const int& val) -> bool {
    std::cout << val << " ";
    return true;
  });

  std::cout << '\n';

  graph.DFS([](const int& val) -> bool {
    std::cout << val << " ";
    return true;
  });

  std::cout << '\n';std::cout << '\n';

  graph.BFSVisit(1, [](const int& val) -> bool {
    std::cout << val << " ";
    return true;
  });

  std::cout << '\n';

  graph.DFSVisit(1, [](const int& val) -> bool {
    std::cout << val << " ";
    return val % 2 != 0;
  });

  std::cout << '\n';

  auto sinks = graph.Sinks();
  for (auto& sink: sinks)
    std::cout << sink << " ";

  std::cout << '\n';

  auto sources = graph.Sources();
  for (auto& source: sources)
    std::cout << source << " ";

  std::cout << '\n';


  return 0;
}