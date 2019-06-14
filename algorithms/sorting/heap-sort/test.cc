#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "heap_sort.h"

TEST_CASE("HeapSort sort sorted array", "[HeapSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  HeapSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("HeapSort sort array with equal elements", "[HeapSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  HeapSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("HeapSort sort unsorted array", "[HeapSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};
  int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
  HeapSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == expected_arr[i]);
}

TEST_CASE("HeapSort sort null pointer", "[HeapSort]") {
  int* arr = nullptr;
  HeapSort(arr, 0);
  REQUIRE(arr == nullptr);
  HeapSort(arr, 10);
  REQUIRE(arr == nullptr);
}
