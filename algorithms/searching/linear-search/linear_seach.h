//
// Created by valentinvstoyanov on 27.04.19.
//

#ifndef LINEAR_SEARCH_LINEAR_SEACH_H
#define LINEAR_SEARCH_LINEAR_SEACH_H

template<typename T>
int LinearSearch(T* arr, int size, const T& element) {
  if (!arr) return -1;

  for (int i = 0; i < size; ++i)
    if (arr[i] == element)
      return i;

  return -1;
}

#endif //LINEAR_SEARCH_LINEAR_SEACH_H
