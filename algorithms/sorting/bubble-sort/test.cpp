#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "bubble_sort.h"

TEST_CASE("Bubble sort sorted array", "[BubbleSort]") {
  const size_t size = 10;
  int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  BubbleSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == i + 1);
}

TEST_CASE("Bubble sort array with equal elements", "[BubbleSort]") {
  const size_t size = 10;
  int arr[size] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  BubbleSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == 1);
}

TEST_CASE("Bubble sort unsorted array", "[BubbleSort]") {
  const size_t size = 10;
  int arr[size] = {6, 1, 2, 2, 10, 1000, 5, 3, 0, -1};
  int expected_arr[size] = {-1, 0, 1, 2, 2, 3, 5, 6, 10, 1000};
  BubbleSort(arr, size);
  for (size_t i = 0; i < size; ++i)
    REQUIRE(arr[i] == expected_arr[i]);
}

TEST_CASE("Bubble sort null pointer", "[BubbleSort]") {
  int* arr = nullptr;
  BubbleSort(arr, 0);
  REQUIRE(arr == nullptr);
  BubbleSort(arr, 10, false);
  REQUIRE(arr == nullptr);
}