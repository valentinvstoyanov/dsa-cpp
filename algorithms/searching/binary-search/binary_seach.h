//
// Created by valentinvstoyanov on 27.04.19.
//

#ifndef BINARY_SEARCH_BINARY_SEACH_H
#define BINARY_SEARCH_BINARY_SEACH_H

template <typename T>
int BinarySearch(T* arr, int size, const T& element) {
  if (!arr) return -1;

  int left = 0, right = size - 1;

  while (left <= right) {
    int mid = (right - left) / 2 + left;

    if (arr[mid] == element) return mid;
    else if (element < arr[mid]) right = mid - 1;
    else left = mid + 1;
  }

  return -1;
}

#endif //BINARY_SEARCH_BINARY_SEACH_H
