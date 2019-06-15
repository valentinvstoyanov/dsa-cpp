#include <iostream>
#include "counting_sort.h"

void Print(int* arr, size_t size) {
  for (size_t i = 0; i < size; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

void Print(int* arr, int* sorted_arr, size_t size) {
  std::cout << "arr = ";Print(arr, size);
  std::cout << "sorted_arr = ";Print(sorted_arr, size);
  std::cout << std::endl;
}

void First() {
  static const int N = 20;
  int arr[] = {47, 65, 20, 66, 25, 53, 64, 69, 72, 22, 74, 25, 53, 15, 42, 36, 4, 69, 86, 19};
  int* sorted_arr = CountingSort(arr, N);
  Print(arr, sorted_arr, N);
  delete[] sorted_arr;
}

void Second() {
  static const int N = 8;
  int arr[] = {-5, -10, 0, -3, 8, 5, -1, 10};
  int* sorted_arr = CountingSort(arr, N);
  Print(arr, sorted_arr, N);
  delete[] sorted_arr;
}

void Third() {
  static const int N = 10;
  int arr[] = {5,5,5,5,5,5,5,5,5,5};
  int* sorted_arr = CountingSort(arr, N);
  Print(arr, sorted_arr, N);
  delete[] sorted_arr;
}

int main() {
  First();
  Second();
  Third();
  return 0;
}