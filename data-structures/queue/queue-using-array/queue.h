//
// Created by valio_stoyanov on 10/23/18.
//

#ifndef QUEUE_USING_ARRAY_QUEUE_H
#define QUEUE_USING_ARRAY_QUEUE_H

#include <iostream>
#include <cassert>

template<typename T>
class Queue {
  T* buffer_;
  size_t capacity_;
  size_t front_;
  size_t back_;

  void Clear();
  void CopyQueue(const Queue&);
  void Resize(size_t);
 public:
  explicit Queue(size_t = 2);
  Queue(const Queue&);
  ~Queue();
  Queue& operator=(const Queue&);

  Queue& operator+=(const T&);
  bool Empty() const;

  void Enqueue(const T&);
  T Dequeue();
};

template<typename T>
void Queue<T>::Clear() {
  delete[] buffer_;
  capacity_ = front_ = back_ = 0;
}

template<typename T>
void Queue<T>::CopyQueue(const Queue& other) {
  Clear();
  if (other.capacity_ == 0) {
    buffer_ = nullptr;
    return;
  }
  buffer_ = new T[other.capacity_];
  capacity_ = other.capacity_;
  for (size_t i = 0; i < other.capacity_; ++i)
    buffer_[i] = other.buffer_[i];
  front_ = other.front_;
  back_ = other.back_;
}

template<typename T>
void Queue<T>::Resize(size_t capacity) {
  T* buffer = new T[capacity];
  for (size_t i = 0; i < capacity_; ++i)
    buffer[i] = buffer_[(front_ + i) % capacity_];
  delete[] buffer_;
  buffer_ = buffer;
  front_ = 0;
  back_ = capacity_ - 1;
  capacity_ = capacity;
}

template<typename T>
Queue<T>::Queue(size_t capacity)
    : buffer_(nullptr), capacity_(0), front_(0), back_(0) {
  if (capacity > 0) {
    buffer_ = new T[capacity];
    capacity_ = capacity;
  }
}

template<typename T>
Queue<T>::Queue(const Queue& other) {
  CopyQueue(other);
}

template<typename T>
Queue<T>::~Queue() {
  delete[] buffer_;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if (this != &other)
    CopyQueue(other);
  return *this;
}

template<typename T>
bool Queue<T>::Empty() const {
  return back_ % capacity_ == front_;
}

template<typename T>
void Queue<T>::Enqueue(const T& val) {
  if ((back_ + 1) % capacity_ == front_)
    Resize(capacity_ == 0 ? 2 : 2 * capacity_);
  buffer_[back_] = val;
  ++back_ %= capacity_;
}

template<typename T>
T Queue<T>::Dequeue() {
  assert(!Empty() && "Dequeue called on empty queue");
  const size_t old_front = front_;
  ++front_ %= capacity_;
  return buffer_[old_front];
}

template<typename T>
Queue<T>& Queue<T>::operator+=(const T& val) {
  Enqueue(val);
  return *this;
}

#endif //QUEUE_USING_ARRAY_QUEUE_H
