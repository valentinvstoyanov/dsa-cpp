//
// Created by valio_stoyanov on 10/12/18.
//

#ifndef DYNAMICARRAY_DYNAMICARRAY_H
#define DYNAMICARRAY_DYNAMICARRAY_H

#include <algorithm>
#include <cassert>

template<typename T>
class DynamicArray {
  T* buffer_;
  size_t size_;
  size_t capacity_;

  void Copy(T* dest, T* src, size_t size) const;
 public:
  explicit DynamicArray(size_t = 1);
  DynamicArray(const DynamicArray&);
  ~DynamicArray();
  DynamicArray& operator=(const DynamicArray&);

  bool operator==(const DynamicArray<T>& other) const;
  bool operator!=(const DynamicArray<T>& other) const;

  DynamicArray<T>& operator+=(const DynamicArray<T>& other);
  DynamicArray<T>& operator+=(const T& val);

  void Clear();

  void Resize(size_t);
  void Reserve(size_t);
  void ShrinkToFit();

  bool Empty() const;

  size_t Size() const;
  size_t Capacity() const;

  T& operator[](size_t);
  const T& operator[](size_t) const;

  T& At(size_t);
  const T& At(size_t) const;

  T& Front();
  const T& Front() const;

  T& Back();
  const T& Back() const;

  void PushBack(const T&);
  void PopBack();

  void PushFront(const T&);
  void PopFront();
};

template<typename T>
DynamicArray<T>::DynamicArray(size_t capacity)
    : buffer_(nullptr), size_(0), capacity_(0) {
  if (capacity == 0) {
    Clear();
    return;
  }
  buffer_ = new T[capacity];
  capacity_ = capacity;
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : buffer_(nullptr), size_(0), capacity_(0) {
  Reserve(other.capacity_);
  Copy(buffer_, other.buffer_, other.size_);
  size_ = other.size_;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
  Clear();
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
  if (this != &other) {
    Clear();
    if (other.capacity_ > 0) {
      buffer_ = new T[other.capacity_];
      Copy(buffer_, other.buffer_, other.size_);
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
  }
  return *this;
}

template<typename T>
void DynamicArray<T>::Clear() {
  delete[] buffer_;
  size_ = 0;
  capacity_ = 0;
}

template<typename T>
void DynamicArray<T>::Resize(size_t size) {
  if (size == 0) {
    Clear();
    return;
  }

  T* buffer = new T[size];
  const size_t min_size = std::min(size, size_);
  Copy(buffer, buffer_, min_size);

  delete[] buffer_;
  buffer_ = buffer;
  size_ = min_size;
  capacity_ = size;
}

template<typename T>
void DynamicArray<T>::Reserve(size_t capacity) {
  if (capacity <= capacity_)
    return;

  T* buffer = new T[capacity];
  Copy(buffer, buffer_, size_);

  delete[] buffer_;
  buffer_ = buffer;
  capacity_ = capacity;
}

template<typename T>
void DynamicArray<T>::ShrinkToFit() {
  if (size_ == 0) {
    Clear();
    return;
  }

  if (size_ == capacity_)
    return;

  T* buffer = new T[size_];
  Copy(buffer, buffer_, size_);

  delete[] buffer_;
  capacity_ = size_;
}

template<typename T>
bool DynamicArray<T>::Empty() const {
  return size_ == 0;
}

template<typename T>
size_t DynamicArray<T>::Size() const {
  return size_;
}

template<typename T>
size_t DynamicArray<T>::Capacity() const {
  return capacity_;
}

template<typename T>
T& DynamicArray<T>::operator[](size_t pos) {
  assert(pos < size_ && "Index out of range");
  return buffer_[pos];
}

template<typename T>
const T& DynamicArray<T>::operator[](size_t pos) const {
  assert(pos < size_ && "Index out of range");
  return buffer_[pos];
}

template<typename T>
T& DynamicArray<T>::At(size_t pos) {
  assert(pos < size_ && "At called with pos out of range");
  return buffer_[pos];
}

template<typename T>
const T& DynamicArray<T>::At(size_t pos) const {
  assert(pos < size_ && "At called with pos out of range");
  return buffer_[pos];
}

template<typename T>
T& DynamicArray<T>::Front() {
  assert(size_ > 0 && "Front method called on empty array");
  return buffer_[0];
}

template<typename T>
const T& DynamicArray<T>::Front() const {
  assert(size_ > 0 && "Front method called on empty array");
  return buffer_[0];
}

template<typename T>
T& DynamicArray<T>::Back() {
  assert(size_ > 0 && "Back method called on empty array");
  return buffer_[size_ - 1];
}

template<typename T>
const T& DynamicArray<T>::Back() const {
  assert(size_ > 0 && "Back method called on empty array");
  return buffer_[size_ - 1];
}

template<typename T>
void DynamicArray<T>::PushBack(const T& val) {
  if (size_ == capacity_)
    Resize(size_ == 0 ? 1 : size_ * 2);
  buffer_[size_++] = val;
}

template<typename T>
void DynamicArray<T>::PopBack() {
  assert(size_ > 0 && "Pop method called on empty array");
  --size_;
}

template<typename T>
void DynamicArray<T>::PushFront(const T& val) {
  if (size_ == capacity_)
    Resize(size_ == 0 ? 1 : size_ * 2);
  Copy(buffer_ + 1, buffer_, size_);
  buffer_[0] = val;
  ++size_;
}

template<typename T>
void DynamicArray<T>::PopFront() {
  assert(size_ > 0 && "Pop method called on empty array");
  for (size_t i = 0; i < size_ - 1; --i)
    buffer_[i] = buffer_[i + 1];
  --size_;
}

template<typename T>
void DynamicArray<T>::Copy(T* dest, T* src, size_t size) const {
  if (src == nullptr || dest == nullptr) return;
  for (size_t i = 0; i < size; ++i)
    dest[i] = src[i];
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) const {
  if (this == &other)
    return true;
  if (size_ != other.size_)
    return false;

  for (size_t i = 0; i < size_; ++i)
    if (buffer_[i] != other.buffer_[i])
      return false;

  return true;
}

template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray<T>& other) const {
  return !(*this == other);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray<T>& other) {
  Resize(size_ + other.size_);
  Copy(buffer_ + size_, other.buffer_, other.size_);
  size_ += other.size_;
  return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const T& val) {
  PushBack(val);
  return *this;
}

#endif //DYNAMICARRAY_DYNAMICARRAY_H
