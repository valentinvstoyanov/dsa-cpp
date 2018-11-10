//
// Created by valio_stoyanov on 10/21/18.
//

#ifndef STACK_USING_ARRAY_STACK_H
#define STACK_USING_ARRAY_STACK_H

#include <algorithm>

template<typename T>
class Stack {
  T* buffer_;
  int top_;
  size_t capacity_;

  void Copy(T* dest, T* src, size_t size) const;
  void CopyStack(const Stack&);
  void Resize(size_t capacity);
 public:
  explicit Stack(size_t = 1);
  Stack(const Stack&);
  ~Stack();

  Stack& operator=(const Stack&);
  Stack& operator+=(const Stack&);
  Stack& operator+=(const T&);
  bool operator==(const Stack&) const;
  bool operator!=(const Stack&) const;

  bool Empty() const;
  size_t Size() const;

  void Push(const T&);
  T Pop();

  void Clear();
};

template<typename T>
void Stack<T>::Clear() {
  delete[] buffer_;
  buffer_ = nullptr;
  top_ = -1;
  capacity_ = 0;
}

template<typename T>
void Stack<T>::Copy(T* dest, T* src, size_t size) const {
  if (src == nullptr || dest == nullptr) return;
  for (size_t i = 0; i < size; ++i)
    dest[i] = src[i];
}

template<typename T>
void Stack<T>::CopyStack(const Stack& other) {
  if (other.capacity_ > 0) {
    buffer_ = new T[other.capacity_];
    capacity_ = other.capacity_;
    Copy(buffer_, other.buffer_, static_cast<size_t>((top_ = other.top_) + 1));
  }
}

template<typename T>
void Stack<T>::Resize(size_t capacity) {
  T* buffer = new T[capacity];
  capacity_ = capacity;
  Copy(buffer, buffer_, static_cast<size_t>(top_ + 1));
  delete[] buffer_;
  buffer_ = buffer;
}

template<typename T>
Stack<T>::Stack(size_t capacity)
    : top_(-1), capacity_(0), buffer_(nullptr) {
  if (capacity > 0) {
    buffer_ = new T[capacity];
    capacity_ = capacity;
  }
}

template<typename T>
Stack<T>::Stack(const Stack& other)
    : top_(-1), capacity_(0), buffer_(nullptr) {
  CopyStack(other);
}

template<typename T>
Stack<T>::~Stack() {
  delete[] buffer_;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this != &other) {
    Clear();
    CopyStack(other);
  }
  return *this;
}

template<typename T>
bool Stack<T>::Empty() const {
  return top_ < 0;
}

template<typename T>
size_t Stack<T>::Size() const {
  return static_cast<size_t>(top_ + 1);
}

template<typename T>
void Stack<T>::Push(const T& val) {
  if (top_ + 1 == capacity_)
    Resize(capacity_ == 0 ? 1 : 2 * capacity_);
  buffer_[++top_] = val;
}

template<typename T>
T Stack<T>::Pop() {
  return buffer_[top_--];
}

template<typename T>
Stack<T>& Stack<T>::operator+=(const Stack& other) {
  const int least_capacity_needed = top_ + other.top_ + 2;
  if (capacity_ < least_capacity_needed)
    Resize(capacity_ == 0 ? 1 : std::max(2 * capacity_, static_cast<size_t>(least_capacity_needed)));
  Copy(buffer_ + top_ + 1, other.buffer_, static_cast<size_t>(other.top_ + 1));
  top_ += other.top_ + 1;
  return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator+=(const T& val) {
  Push(val);
  return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack& other) const {
  if (this == &other)
    return true;
  if (top_ != other.top_)
    return false;
  for (int i = 0; i <= top_; ++i)
    if (buffer_[i] != other.buffer_[i])
      return false;

  return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack& other) const {
  return !(*this == other);
}


#endif //STACK_USING_ARRAY_STACK_H
