#include <iostream>
#include "disjoint_set.h"

int main() {
  std::vector<int> v = {1, 3, 7, 8, 2, 5, 100};
  std::unordered_map<int, size_t> mapping = DisjointSet::DefaultMapping(v);

  DisjointSet ds(v.size());
  printf("%d\n", ds.SameSet(mapping[1], mapping[100]));
  ds.Union(mapping[1], mapping[100]);
  printf("%d\n", ds.SameSet(mapping[1], mapping[100]));

  return 0;
}