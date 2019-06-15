#include <iostream>
#include "max_min.h"

int main() {
  int arr[10] = {-199, 20, -200, 50, 1000, 1000, - 201, 1541, 0, 1};
  auto mm = MaxMin(arr, 10);
  std::cout << "max = " << mm.first << ", min = " << mm.second << std::endl;
  std::cout << "max = " << Max(arr, 10) << std::endl;
  std::cout << "max = " << Max(arr, 0) << std::endl;
  std::cout << "max = " << Max<int>(nullptr, 1) << std::endl;
  std::cout << "min = " << Min(arr, 10) << std::endl;
  std::cout << "min = " << Min(arr, 0) << std::endl;
  std::cout << "min = " << Min<int>(nullptr, 10) << std::endl;
  return 0;
}