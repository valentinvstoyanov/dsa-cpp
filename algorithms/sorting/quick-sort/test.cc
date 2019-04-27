#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "quick_sort.h"

TEST_CASE("Quick sort sorted array", "[QuickSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  QuickSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("Quick sort array with equal elements", "[QuickSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  QuickSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("Quick sort unsorted array", "[QuickSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};

  const int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
  QuickSort(arr, size);

  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == expected_arr[i]);
}

TEST_CASE("Quick sort null pointer", "[QuickSort]") {
  int* arr = nullptr;
  QuickSort(arr, 0);
  REQUIRE(arr == nullptr);
  REQUIRE(arr == nullptr);
}
