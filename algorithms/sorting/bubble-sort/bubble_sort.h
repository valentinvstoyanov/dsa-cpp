//
// Created by valio_stoyanov on 11/6/18.
//

#ifndef BUBBLE_SORT_BUBBLE_SORT_H
#define BUBBLE_SORT_BUBBLE_SORT_H

#include <algorithm>

template<typename T>
void BubbleSort(T* arr, size_t size, bool ascending = true) {
  bool swapped = true;
  for (size_t i = 0; swapped && i < size; ++i) {
    swapped = false;
    for (size_t j = 0; j < size - i - 1; ++j) {
      if (ascending ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
  }
}

#endif //BUBBLE_SORT_BUBBLE_SORT_H
