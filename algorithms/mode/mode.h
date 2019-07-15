#ifndef MODE_MODE_H
#define MODE_MODE_H

#include "../sorting/quick-sort/quick_sort.h"

template <typename T>
int Mode(T* arr, int size) {
  if (size == 0 || !arr) return -1;
  if (size == 1) return arr[0];

  QuickSort(arr, size);

  int mode_idx = 0;
  int mode_count = 1;

  for (int i = 1; i < size; ++i) {
    if (arr[i] != arr[i - 1]) {
      int j = i + 1;
      while (arr[j] == arr[i])
        ++j;
      if (j - i > mode_count) {
        mode_count = j - i;
        mode_idx = i;
      }
      i = j;
    } else {
      ++mode_count;
    }
  }

  return mode_count == 1 ? -1 : arr[mode_idx];
}

#endif //MODE_MODE_H
