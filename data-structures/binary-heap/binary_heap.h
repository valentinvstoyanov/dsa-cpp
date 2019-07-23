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
  explicit BinaryHeap(Comparator = Comparator());
  explicit BinaryHeap(std::vector<T>, Comparator = Comparator());

  static size_t Left(size_t);
  static size_t Right(size_t);
  static size_t Parent(size_t);
  static size_t ParentN(size_t, size_t);

  static void Heapify(T*, size_t, size_t, Comparator = std::less<T>());
  static void BuildHeap(T*, size_t, Comparator = std::less<T>());

  bool IsEmpty() const;
  size_t Size() const;

  void UpdateKey(size_t index, const T& key);
  void UpdateTopKey(const T& value);
  void Insert(const T&);
  const T& Top() const;
  T Extract();
};

template<typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap(Comparator comparator) : comparator_(comparator) {}

template<typename T, typename Comparator>
BinaryHeap<T, Comparator>::BinaryHeap(std::vector<T> arr, Comparator comparator)
    : arr_(arr), comparator_(comparator) {
  BuildHeap(arr_.data(), arr.size(), comparator_);
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Left(size_t i) {
  return 2 * i + 1;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Right(size_t i) {
  return 2 * i + 2;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::Parent(size_t i) {
  return (i - 1) / 2;
}

template<typename T, typename Comparator>
size_t BinaryHeap<T, Comparator>::ParentN(size_t i, size_t n) {
  return i == 0 ? 0 : Parent(ParentN(i, n - 1));
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::Heapify(T* arr, size_t size, size_t i, Comparator before) {
  if (!arr || size == 0)
    return;

  assert(i < size && "Heapify called with i out of bounds.");

  size_t largest = i;
  size_t left = Left(i);
  size_t right = Right(i);

  if (left < size && before(arr[largest], arr[left]))
    largest = left;

  if (right < size && before(arr[largest], arr[right]))
    largest = right;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    Heapify(arr, size, largest, before);
  }
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::BuildHeap(T* arr, size_t size, Comparator before) {
  for (long i = size / 2 - 1; i >= 0; --i)
    Heapify(arr, size, static_cast<size_t>(i), before);
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
void BinaryHeap<T, Comparator>::UpdateKey(size_t index, const T& key) {
  assert(index < Size() && "Update key index out of bounds.");
  assert(!IsEmpty() && "Update key called on empty binary heap.");
  assert(!comparator_(key, Top()) && "Cannot decrease key of max heap.");

  arr_[index] = key;
  while (index > 0) {
    size_t parent_i = Parent(index);

    if (comparator_(arr_[parent_i], arr_[index])) {
      std::swap(arr_[parent_i], arr_[index]);
      index = parent_i;
    } else {
      break;
    }
  }
}

template<typename T, typename Comparator>
void BinaryHeap<T, Comparator>::UpdateTopKey(const T& key) {
  UpdateKey(0, key);
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
  Heapify(arr_.data(), arr_.size(), 0, comparator_);
  return top;
}

#endif //BINARY_HEAP_BINARY_HEAP_H
