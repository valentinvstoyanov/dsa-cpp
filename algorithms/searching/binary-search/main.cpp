#include <iostream>
#include <cassert>
#include "binary_seach.h"

int main() {
  const int size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < size; ++i)
    assert(BinarySearch(arr, size, i + 1) == i && "fail");
  assert(BinarySearch(arr, size, 111111) == -1 && "fail");
  assert(BinarySearch<int>(nullptr, 0, 10) == -1 && "fail");

  for (int i = 0; i < size; ++i)
    assert(BinarySearchRecursive(arr, i + 1, 0, size) == i && "fail");
  assert(BinarySearchRecursive(arr, 111111, 0, size) == -1 && "fail");
  assert(BinarySearchRecursive<int>(nullptr, 0, 0, size) == -1 && "fail");

  std::cout << "Success!" << std::endl;

  return 0;
}