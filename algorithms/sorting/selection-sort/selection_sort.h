//
// Created by valio_stoyanov on 11/14/18.
//

#ifndef SELECTION_SORT_SELECTION_SORT_H
#define SELECTION_SORT_SELECTION_SORT_H

#include <algorithm>

template<typename T>
void SelectionSort(T* arr, size_t size, bool ascending = true) {
  if (!arr) return;
  for (size_t i = 0; i < size - 1; ++i) {
    size_t index = i;
    for (size_t j = i + 1; j < size; ++j)
      if (ascending ? arr[j] < arr[index] : arr[j] > arr[index])
        index = j;
    if (index != i) std::swap(arr[index], arr[i]);
  }
}

#endif //SELECTION_SORT_SELECTION_SORT_H
