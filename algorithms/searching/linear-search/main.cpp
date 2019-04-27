#include <iostream>
#include <cassert>
#include "linear_seach.h"

int main() {
  const int size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (int i = 0; i < size; ++i)
    assert(LinearSearch(arr, size, i + 1) == i && "fail");
  assert(LinearSearch(arr, size, 111111) == -1 && "fail");
  assert(LinearSearch<int>(nullptr, 0, 10) == -1 && "fail");

  std::cout << "Success!" << std::endl;

  return 0;
}