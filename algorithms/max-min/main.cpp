#include <iostream>
#include "max_min.h"

int main() {
  int arr[10] = {-199, 20, -200, 50, 1000, 1000, - 201, 1541, 0, 1};
  auto mm = MaxMin(arr, 10);
  std::cout << "max = " << mm.first << ", min = " << mm.second << std::endl;
  return 0;
}