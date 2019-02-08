#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "merge_sort.h"

TEST_CASE("Merge sort sorted array", "[MergeSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  MergeSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("Merge sort array with equal elements", "[MergeSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  MergeSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("Merge sort unsorted array", "[MergeSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};

  const int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
  MergeSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == expected_arr[i]);
}

TEST_CASE("Merge sort null pointer", "[MergeSort]") {
  int* arr = nullptr;
  MergeSort(arr, 0);
  REQUIRE(arr == nullptr);
  REQUIRE(arr == nullptr);
}