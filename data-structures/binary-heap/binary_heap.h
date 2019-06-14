//
// Created by valentinvstoyanov on 14.06.19.
//

#ifndef BINARY_HEAP_BINARY_HEAP_H
#define BINARY_HEAP_BINARY_HEAP_H

#include <vector>
#include <functional>
#include <cassert>

template<typename T, typename Comparator = std::less<T>>
class BinaryHeap {
  std::vector<T> arr_;
  Comparator comparator_;
 public:
  explicit BinaryHeap(Comparator = std::less<T>());
  explicit BinaryHeap(std::vector<T>, Comparator = std::less<T>());

  size_t Left(size_t) const;
  size_t Right(size_t) const;
  size_t Parent(size_t) const;
  size_t ParentN(size_t, size_t) const;

  bool IsEmpty() const;
  size_t Size() const;

  void Heapify(size_t);
  void Insert(const T&);
  const T& Top() const;
  T Extract();
};

template<typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap(Comparator comparator) : comparator_(comparator) {}

template<typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap(std::vector<T> arr, Comparator comparator) : arr_(arr), comparator_(comparator) {
  for (int i = arr_.size() / 2; i >= 0; --i)
    Heapify(i);
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Left(size_t i) const {
  return 2 * i + 1;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Right(size_t i) const {
  return 2 * i + 2;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Parent(size_t i) const {
  return (i - 1) / 2;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::ParentN(size_t i, size_t n) const {
  return i == 0 ? 0 : Parent(ParentN(i, n - 1));
}

template<typename T, typename Comparator>
bool BinaryHeap<T, Comparator>::IsEmpty() const {
  return arr_.empty();
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Size() const {
  return arr_.size();
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Heapify(size_t i) {
  if (IsEmpty())
    return;

  assert(i < arr_.size() && "Heapify called with index out of bounds.");

  size_t left = Left(i);
  size_t right = Right(i);
  size_t largest = i;

  if (left < arr_.size() && comparator_(arr_[largest], arr_[left]))
    largest = left;

  if (right < arr_.size() && comparator_(arr_[largest], arr_[right]))
    largest = right;

  if (largest != i) {
    std::swap(arr_[i], arr_[largest]);
    Heapify(largest);
  }
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Insert(const T& element) {
  arr_.push_back(element);
  size_t i = arr_.size() - 1;
  while (i > 0) {
    size_t parent_i = Parent(i);

    if (comparator_(arr_[parent_i], arr_[i])) {
      std::swap(arr_[parent_i], arr_[i]);
      i = parent_i;
    } else {
      break;
    }
  }
}

template<typename T, typename Comparator>
const T& BinaryHeap<T, Comparator>::Top() const {
  assert(!IsEmpty() && "Top called on empty heap.");
  return arr_.front();
}

template<typename T, typename Comparator>
T BinaryHeap<T, Comparator>::Extract() {
  assert(!IsEmpty() && "Extract called on empty heap.");
  T top = arr_.front();
  arr_.front() = arr_.back();
  arr_.pop_back();
  Heapify(0);
  return top;
}

#endif //BINARY_HEAP_BINARY_HEAP_H
