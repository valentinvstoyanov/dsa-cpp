//
// Created by valentinvstoyanov on 06.02.19.
//

#ifndef QUICK_SORT_QUICK_SORT_H
#define QUICK_SORT_QUICK_SORT_H

#include <algorithm>
#include <iostream>

template <typename T>
int Partition(T* arr, int low, int high) {
  const T& pivot = arr[high];
  int pp = low;

  for (int i = low; i < high; ++i) {
    if (arr[i] < pivot) {
      std::swap(arr[i], arr[pp]);
      ++pp;
    }
  }

  std::swap(arr[pp], arr[high]);
  return pp;
}

template <typename T>
void QuickSort(T* arr, int low, int high) {
  if (low < high) {
    const int mid = Partition(arr, low, high);

    QuickSort(arr, low, mid - 1);
    QuickSort(arr, mid + 1, high);
  }
}

template <typename T>
void QuickSort(T* arr, int size) {
  if (!arr)
    return;

  QuickSort(arr, 0, size - 1);
}

#endif //QUICK_SORT_QUICK_SORT_H
