#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "insertion_sort.h"

TEST_CASE("Insertion sort sorted array", "[InsertionSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  InsertionSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("Insertion sort array with equal elements", "[InsertionSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  InsertionSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("Insertion sort unsorted array", "[InsertionSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};

  SECTION("Ascending") {
    const int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
    InsertionSort(arr, size);
    for (size_t i = 0; i < size; ++i)
      REQUIRE(arr[i] == expected_arr[i]);
  }

  SECTION("Descending") {
    const int expected_arr[size] = {1000, 10, 6, 5, 3, 2, 2, 1, 0, -1};
    InsertionSort(arr, size, false);
    for (size_t i = 0; i < size; ++i)
      REQUIRE(arr[i] == expected_arr[i]);
  }
}