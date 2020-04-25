#ifndef LIS_DP__LONGEST_INCREASING_SUBSEQUENCE_H_
#define LIS_DP__LONGEST_INCREASING_SUBSEQUENCE_H_

#include "../../max-min/max_min.h"

template <typename T>
int LIS(T* arr, size_t size) {
  if (arr == nullptr || size == 0) return 0;
  if (size == 1) return 1;

  int* sol = new int[size];
  for (size_t i = 0; i < size; ++i) sol[i] = 1;

  size_t j = 0;
  size_t i = 1;
  while(i < size) {
    if (arr[j] < arr[i])
      if (sol[j] + 1 > sol[i]) sol[i] = sol[j] + 1;

    ++j;
    if (j == i) {
      j = 0;
      ++i;
    }
  }

  const int max_len = Max(sol, size);
  delete[] sol;

  return max_len;
}

#endif //LIS_DP__LONGEST_INCREASING_SUBSEQUENCE_H_
