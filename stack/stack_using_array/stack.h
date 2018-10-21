//
// Created by valio_stoyanov on 10/21/18.
//

#ifndef STACK_USING_ARRAY_STACK_H
#define STACK_USING_ARRAY_STACK_H

#include <cstddef>

template<typename T>
class Stack {
  T* buffer_;
  int top_;
  size_t capacity_;

  void Clear();
  void Copy(T* dest, T* src, size_t size) const;
 public:
  Stack(size_t = 1);
  Stack(const Stack&);
  ~Stack();
  Stack& operator=(const Stack&);

  bool Empty() const;

  void Push(const T&);
  T Pop();
};

template<typename T>
void Stack<T>::Clear() {
  delete[] buffer_;
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
Stack<T>::Stack(size_t capacity)
    : top_(-1), capacity_(0), buffer_(nullptr) {
  if (capacity > 0) {
    buffer_ = new T[capacity];
    capacity_ = capacity_;
  }
}

template<typename T>
Stack<T>::Stack(const Stack& other)
    : top_(other.top_), capacity_(other.capacity_), buffer_(nullptr) {
  if (other.capacity_ > 0) {
    buffer_ = new T[other.capacity_];
    Copy(buffer_, other.buffer_, static_cast<size_t>(other.top_ + 1));
  }
}

template<typename T>
Stack<T>::~Stack() {
  Clear();
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this != &other) {
    Clear();
    if (other.capacity_ > 0) {
      buffer_ = new T[other.capacity_];
      Copy(buffer_, other.buffer_, static_cast<size_t>(other.top_ + 1));
      top_ = other.top_;
      capacity_ = other.capacity_;
    }
  }

  return *this;
}

template<typename T>
bool Stack<T>::Empty() const {
  return top_ < 0;
}

template<typename T>
void Stack<T>::Push(const T& val) {
  if (top_ + 1 == capacity_) {
    capacity_ = capacity_ == 0 ? 1 : 2 * capacity_;
    T* buffer = new T[capacity_];
    Copy(buffer, buffer_, static_cast<size_t>(top_ + 1));
    delete[] buffer_;
    buffer_ = buffer;
  }
  buffer_[++top_] = val;
}

template<typename T>
T Stack<T>::Pop() {
  return buffer_[top_--];
}

#endif //STACK_USING_ARRAY_STACK_H
