#ifndef CLOSEST_PAIR_CLOSEST_PAIR_H
#define CLOSEST_PAIR_CLOSEST_PAIR_H

#include "../sorting/quick-sort/quick_sort.h"

template <typename T>
std::pair<int, int> ClosestPair(T* arr, int size) {
  if (size == 0 || !arr) return std::make_pair(-1, -1);
  if (size == 1) return std::make_pair(0, 0);

  QuickSort(arr, size);

  int first_idx = 0;
  int second_idx = 1;

  for (int i = 2; i < size; ++i) {
    if (arr[i] - arr[i - 1] < arr[second_idx] - arr[first_idx]) {
      first_idx = i - 1;
      second_idx = i;
    }
  }

  return std::make_pair(first_idx, second_idx);
}

#endif //CLOSEST_PAIR_CLOSEST_PAIR_H
