#include <iostream>
#include "radix_sort.h"

void Print(int arr[], size_t n) {
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
}

int main() {
  const size_t n = 10;
  int arr[n] = {170, 145, 675, 590, 802, 224, 422, 966, 1, 20};

  int* sorted_arr = RadixSort(arr, n);
  if (sorted_arr)
    Print(sorted_arr, n);

  return 0;
}