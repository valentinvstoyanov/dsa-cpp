#ifndef RADIX_SORT_RADIX_SORT_H
#define RADIX_SORT_RADIX_SORT_H

#include <cstring>
#include <cmath>
#include "../../max-min/max_min.h"
#include "../../count-digits/count_digits.h"

template<typename T>
void CS(T* arr, size_t size, int exp, T* res) {
  int count[11] = {0};
  for (int i = 0; i < size; ++i) ++count[(arr[i] / exp) % 10];
  for (int i = 1; i < 10; ++i) count[i] += count[i - 1];
  for (int i = size - 1; i >= 0; --i) {
    res[count[(arr[i] / exp) % 10] - 1] = arr[i];
    --count[(arr[i] / exp) % 10];
  }
  for (int i = 0; i < size; ++i) arr[i] = res[i];
}

template<typename T>
T* RadixSort(T* arr, size_t size) {
  if (!arr || size == 0)
    return nullptr;

  T* res = new T[size];

  auto max = Max(arr, size);
  int digits = CountDigitsIter(max);

  int exp = 1;
  for (int i = 1; i <= digits; ++i) {
    CS(arr, size, exp, res);
    exp *= 10;
  }

  delete[] res;

  return arr;
}

#endif //RADIX_SORT_RADIX_SORT_H
