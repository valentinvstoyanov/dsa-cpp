//
// Created by valentinvstoyanov on 06.02.19.
//

#ifndef MERGE_SORT_MERGE_SORT_H
#define MERGE_SORT_MERGE_SORT_H

#include <cstddef>

template<typename T>
void Merge(T* arr, size_t low, size_t medium, size_t high) {
  T* temp = new T[high - low + 1];

  size_t temp_counter = 0;
  size_t left_counter = low;
  size_t right_counter = medium + 1;

  while (left_counter <= medium && right_counter <= high)
    temp[temp_counter++] = arr[left_counter] <= arr[right_counter] ? arr[left_counter++] : arr[right_counter++];

  while (left_counter <= medium)
    temp[temp_counter++] = arr[left_counter++];

  while (right_counter <= high)
    temp[temp_counter++] = arr[right_counter++];

  left_counter = low;
  temp_counter = 0;

  while (left_counter <= high)
    arr[left_counter++] = temp[temp_counter++];

  delete[] temp;
}

template<typename T>
void MergeSort(T* arr, size_t low, size_t high) {
  if (low < high) {
    size_t medium = low + (high - low) / 2;
    MergeSort(arr, low, medium);
    MergeSort(arr, medium + 1, high);
    Merge(arr, low, medium, high);
  }
}

template<typename T>
void MergeSort(T* arr, size_t size) {
  if (!arr)
    return;

  MergeSort(arr, 0, size - 1);
}

#endif //MERGE_SORT_MERGE_SORT_H
