//
// Created by valio_stoyanov on 11/12/18.
//

#ifndef STACK_USING_LINKED_LIST_STACK_H
#define STACK_USING_LINKED_LIST_STACK_H

#include <cassert>
#include <cstddef>
#include <iostream>

template<typename T>
class Stack {
  struct Node {
    T data_;
    Node* next_;
    explicit Node(T data);
  };
  Node* top_;
  size_t size_;
  void CopyStack(const Stack&);
 public:
  Stack();
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
Stack<T>::Node::Node(T data)
    : data_(data), next_(nullptr) {}

template<typename T>
void Stack<T>::CopyStack(const Stack& other) {
  if (other.Empty()) return;
  Push(other.top_->data_);
  Node* other_curr = other.top_;
  Node* this_curr = top_;
  while (other_curr->next_) {
    this_curr->next_ = new Node(other_curr->next_->data_);
    other_curr = other_curr->next_;
    this_curr = this_curr->next_;
    ++size_;
  }
}

template<typename T>
Stack<T>::Stack()
    : top_(nullptr), size_(0) {}

template<typename T>
Stack<T>::Stack(const Stack& other)
    : top_(nullptr), size_(0) {
  CopyStack(other);
}

template<typename T>
Stack<T>::~Stack() {
  Clear();
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
Stack<T>& Stack<T>::operator+=(const Stack& rhs) {
  if (!rhs.Empty()) {
    Node* llist_head = new Node(rhs.top_->data_);
    Node* llist = llist_head;
    Node* rhs_curr = rhs.top_;
    while(rhs_curr->next_) {
      Node* node = new Node(rhs_curr->next_->data_);
      llist->next_ = node;
      llist = llist->next_;
      rhs_curr = rhs_curr->next_;
    }
    llist->next_ = top_;
    top_ = llist_head;
    size_ += rhs.size_;
  }
  return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator+=(const T& val) {
  Push(val);
  return *this;
}

template<typename T>
bool Stack<T>::operator==(const Stack& other) const {
  if (this == &other) return true;
  if (size_ != other.size_) return false;

  Node* this_curr = top_;
  Node* other_curr = other.top_;
  for (size_t i = 0; i < size_; ++i) {
    if (this_curr->data_ != other_curr->data_) return false;
    this_curr = this_curr->next_;
    other_curr = other_curr->next_;
  }

  return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack& other) const {
  return !(*this == other);
}

template<typename T>
bool Stack<T>::Empty() const {
  return top_ == nullptr;
}

template<typename T>
size_t Stack<T>::Size() const {
  return size_;
}

template<typename T>
void Stack<T>::Push(const T& val) {
  Node* node = new Node(val);
  node->next_ = top_;
  top_ = node;
  ++size_;
}

template<typename T>
T Stack<T>::Pop() {
  assert(!Empty() && "Pop called on empty stack");
  Node* first = top_;
  T result = first->data_;
  top_ = first->next_;
  delete first;
  --size_;
  return result;
}

template<typename T>
void Stack<T>::Clear() {
  while (!Empty()) Pop();
}

#endif //STACK_USING_LINKED_LIST_STACK_H
