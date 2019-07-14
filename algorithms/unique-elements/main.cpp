#include <iostream>

#include "unique_elements.h"

int main() {
  int arr1[] = {1, 2, 3, 5, 100, 0, 20, 30};
  std::cout << HasUniqueElements(arr1, 8) << "\n";

  int arr2[] = {20, 10, 25, 40, 20, 1, 2, 3};
  std::cout << HasUniqueElements(arr2, 8) << "\n";
  return 0;
}