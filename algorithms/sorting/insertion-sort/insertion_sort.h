//
// Created by valio_stoyanov on 11/7/18.
//

#ifndef INSERTION_SORT_INSERTION_SORT_H
#define INSERTION_SORT_INSERTION_SORT_H

#include <algorithm>

template<typename T>
void InsertionSort(T* arr, size_t size, bool ascending = true) {
  for (size_t i = 1; i < size; ++i)
    for (size_t j = i; j > 0 && (ascending ? arr[j] < arr[j - 1] : arr[j] > arr[j - 1]); --j)
      std::swap(arr[j], arr[j - 1]);
}

#endif //INSERTION_SORT_INSERTION_SORT_H
