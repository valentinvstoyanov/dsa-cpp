#include <iostream>
#include "closest_pair.h"

void PrintCP(const std::pair<int, int>& cp, int* arr) {
  if (cp.first < 0 && cp.second < 0) {
    std::cout << "No elements\n";
    return;
  }

  std::cout << "(" << arr[cp.first] << ", " << arr[cp.second] << "); d = " << arr[cp.second] - arr[cp.first] << ".\n";
}

void Example1() {
  int arr[12] = {12, 10, 2, 3, 17, 100, 60, 2, 3, 4, 1, 1};
  PrintCP(ClosestPair(arr, 12), arr);
}

void Example2() {
  int arr[0];
  PrintCP(ClosestPair(arr, 0), arr);
}

void Example3() {
  int* arr = nullptr;
  PrintCP(ClosestPair(arr, 10), arr);
}

void Example4() {
  int arr[] = {1};
  PrintCP(ClosestPair(arr, 1), arr);
}

int main() {
  Example1();
  Example2();
  Example3();
  Example4();
  return 0;
}