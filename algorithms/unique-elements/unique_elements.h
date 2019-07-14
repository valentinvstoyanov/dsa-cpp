#ifndef UNIQUE_ELEMENTS_UNIQUE_ELEMENTS_H
#define UNIQUE_ELEMENTS_UNIQUE_ELEMENTS_H

#include "../closest-pair/closest_pair.h"

template <typename T>
bool HasUniqueElements(T* arr, int size) {
  std::pair<int, int> p = ClosestPair(arr, size);
  return arr[p.second] - arr[p.first] > 0;
}

#endif //UNIQUE_ELEMENTS_UNIQUE_ELEMENTS_H
