//
// Created by valio_stoyanov on 11/14/18.
//

#ifndef QUEUE_USING_LINKED_LIST_QUEUE_H
#define QUEUE_USING_LINKED_LIST_QUEUE_H

#include <cassert>
#include <cstddef>

template <typename T>
class Queue {
  struct Node {
    T data_;
    Node* next_;
    explicit Node(T);
  };

  Node* head_;
  Node* tail_;
  size_t size_;
  void CopyQueue(const Queue&);
 public:
  Queue();
  ~Queue();

  Queue(const Queue&);
  Queue& operator=(const Queue&);

  void Clear();

  void Enqueue(const T&);
  T Dequeue();

  bool Empty() const;
  size_t Size() const;

  bool operator==(const Queue&) const;
  bool operator!=(const Queue&) const;
  Queue& operator+=(const Queue&);
  Queue& operator+=(const T&);
};

template<typename T>
Queue<T>::Node::Node(T data)
    : data_(data), next_(nullptr) {}

template<typename T>
Queue<T>::Queue()
    : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
void Queue<T>::Clear() {
  while (!Empty()) Dequeue();
}

template<typename T>
void Queue<T>::CopyQueue(const Queue& other) {
  if (other.Empty()) return;
  Enqueue(other.head_->data_);
  Node* this_curr = head_;
  Node* other_curr = other.head_;
  while (other_curr->next_) {
    Node* node = new Node(other_curr->next_->data_);
    this_curr = this_curr->next_ = node;
    other_curr = other_curr->next_;
    ++size_;
  }
  tail_ = this_curr;
}

template<typename T>
Queue<T>::~Queue() {
 Clear();
}

template<typename T>
Queue<T>::Queue(const Queue& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
  CopyQueue(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if (this != &other) {
    Clear();
    CopyQueue(other);
  }
  return *this;
}

template<typename T>
void Queue<T>::Enqueue(const T& val) {
  if (Empty()) head_ = tail_ = new Node(val);
  else tail_ = tail_->next_ = new Node(val);
  ++size_;
}

template<typename T>
T Queue<T>::Dequeue() {
  assert(!Empty() && "Dequeue called on empty queue");
  T res = head_->data_;
  Node* first = head_;
  head_ = head_->next_;
  if (!head_) tail_ = nullptr;
  delete first;
  --size_;
  return res;
}

template<typename T>
bool Queue<T>::Empty() const {
  return head_ == nullptr;
}

template<typename T>
size_t Queue<T>::Size() const {
  return size_;
}

template<typename T>
Queue<T>& Queue<T>::operator+=(const T& val) {
  Enqueue(val);
  return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator+=(const Queue& rhs) {
  if (!rhs.Empty()) {
    Node* llist_head = new Node(rhs.head_->data_);
    Node* llist = llist_head;
    Node* rhs_curr = rhs.head_;
    while(rhs_curr->next_) {
      Node* node = new Node(rhs_curr->next_->data_);
      llist->next_ = node;
      llist = llist->next_;
      rhs_curr = rhs_curr->next_;
    }
    if (Empty()) {
      head_ = tail_ = llist_head;
    } else {
      tail_->next_ = llist_head;
      tail_ = llist;
    }
    size_ += rhs.size_;
  }
  return *this;
}

template<typename T>
bool Queue<T>::operator==(const Queue& other) const {
  if (this == &other) return true;
  if (size_ != other.size_) return false;

  Node* this_curr = head_;
  Node* other_curr = other.head_;
  for (size_t i = 0; i < size_; ++i) {
    if (this_curr->data_ != other_curr->data_) return false;
    this_curr = this_curr->next_;
    other_curr = other_curr->next_;
  }
  return true;
}

template<typename T>
bool Queue<T>::operator!=(const Queue& other) const {
  return !(*this == other);
}

#endif //QUEUE_USING_LINKED_LIST_QUEUE_H
