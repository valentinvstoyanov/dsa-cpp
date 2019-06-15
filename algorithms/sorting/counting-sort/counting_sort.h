#ifndef COUNTING_SORT_COUNTING_SORT_H
#define COUNTING_SORT_COUNTING_SORT_H

#include <cstddef>
#include <limits>
#include "../../max-min/max_min.h"

template<typename T>
T* CountingSort(T* arr, size_t size) {
  if (!arr || size == 0)
    return nullptr;

  std::pair<T, T> maxMin = MaxMin(arr, size);
  T range = maxMin.first - maxMin.second + 1;
  unsigned* count = new unsigned[range]();

  for (size_t i = 0; i < size; ++i)
    ++count[arr[i] - maxMin.second];

  for (size_t i = 1; i < range; ++i)
    count[i] += count[i - 1];

  T* result = new T[size];
  for (size_t i = 0; i < size; ++i) {
    result[count[arr[i] - maxMin.second] - 1] = arr[i];
    --count[arr[i] - maxMin.second];
  }

  delete[] count;

  return result;
}

#endif //COUNTING_SORT_COUNTING_SORT_H
