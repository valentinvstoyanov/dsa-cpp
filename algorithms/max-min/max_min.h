#ifndef MAX_MIN_MAX_MIN_H
#define MAX_MIN_MAX_MIN_H

#include <cstddef>
#include <limits>
#include <utility>

template<typename T>
std::pair<T, T> MaxMin(T* arr, size_t size) {
  if (!arr || size == 0)
    return std::make_pair(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

  size_t max_idx = 0;
  size_t min_idx = 0;

  for (size_t i = 0; i < size; ++i) {
    if (arr[i] > arr[max_idx]) max_idx = i;
    else if (arr[i] < arr[min_idx]) min_idx = i;
  }

  return std::make_pair(arr[max_idx], arr[min_idx]);
}

#endif //MAX_MIN_MAX_MIN_H
