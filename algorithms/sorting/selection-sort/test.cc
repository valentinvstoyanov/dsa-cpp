#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "selection_sort.h"

TEST_CASE("Selection sort sorted array", "[SelectionSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  SelectionSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("Selection sort array with equal elements", "[SelectionSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  SelectionSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("Selection sort unsorted array", "[SelectionSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};
  int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
  SelectionSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == expected_arr[i]);
}

TEST_CASE("Selection sort null pointer", "[SelectionSort]") {
  int* arr = nullptr;
  SelectionSort(arr, 0);
  REQUIRE(arr == nullptr);
  SelectionSort(arr, 10, false);
  REQUIRE(arr == nullptr);
}