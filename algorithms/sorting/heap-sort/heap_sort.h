//
// Created by valentinvstoyanov on 14.06.19.
//

#ifndef HEAP_SORT_HEAP_SORT_H
#define HEAP_SORT_HEAP_SORT_H

#include "../../../data-structures/binary-heap/binary_heap.h"

template<typename T>
void HeapSort(T* arr, size_t size) {
  if (!arr || size == 0)
    return;

  BinaryHeap<T>::BuildHeap(arr, size);

  for (long i = size - 1; i > 0; --i) {
    std::swap(arr[0], arr[i]);
    BinaryHeap<T>::Heapify(arr, i, 0);
  }
}

#endif //HEAP_SORT_HEAP_SORT_H
