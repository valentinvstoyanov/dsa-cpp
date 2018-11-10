//
// Created by valio_stoyanov on 11/5/18.
//

#ifndef CYCLIC_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H
#define CYCLIC_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <cassert>

template<typename T>
class DoublyLinkedList {
  struct Node {
    T data_;
    Node* next_;
    Node* prev_;
    Node() = default;
    explicit Node(T data);
  } sentinel_;
  size_t size_;
  void CopyList(const DoublyLinkedList&);
 public:
  DoublyLinkedList();
  ~DoublyLinkedList();

  DoublyLinkedList(const DoublyLinkedList&);
  DoublyLinkedList& operator=(const DoublyLinkedList&);

  bool operator==(const DoublyLinkedList&) const;
  bool operator!=(const DoublyLinkedList&) const;
  DoublyLinkedList& operator+=(const DoublyLinkedList&);
  DoublyLinkedList& operator+=(const T&);

  void PushBack(const T&);
  void PushFront(const T&);
  void PopBack();
  void PopFront();

  T& Back();
  T& Front();
  const T& Back() const;
  const T& Front() const;

  size_t Size() const;
  bool Empty() const;

  void Clear();
};

template<typename T>
DoublyLinkedList<T>::Node::Node(T data)
    : data_(data) {}

template<typename T>
void DoublyLinkedList<T>::CopyList(const DoublyLinkedList& other) {
  Node* o_current = other.sentinel_.next_;
  while (o_current != &other.sentinel_) {
    PushBack(o_current->data_);
    o_current = o_current->next_;
  }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : sentinel_(Node()), size_(0) {
  sentinel_.prev_ = sentinel_.next_ = &sentinel_;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Clear();
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
    : sentinel_(Node()), size_(0) {
  sentinel_.prev_ = sentinel_.next_ = &sentinel_;
  CopyList(other);
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
  if (this != &other) {
    Clear();
    CopyList(other);
  }
  return *this;
}

template<typename T>
void DoublyLinkedList<T>::PushBack(const T& val) {
  Node* node = new Node(val);
  node->prev_ = sentinel_.prev_;
  node->next_ = &sentinel_;
  sentinel_.prev_->next_ = node;
  sentinel_.prev_ = node;
  ++size_;
}

template<typename T>
void DoublyLinkedList<T>::PushFront(const T& val) {
  Node* node = new Node(val);
  node->next_ = sentinel_.next_;
  node->prev_ = &sentinel_;
  sentinel_.next_->prev_ = node;
  sentinel_.next_ = node;
  ++size_;
}

template<typename T>
void DoublyLinkedList<T>::PopBack() {
  assert(size_ > 0 && "PopBack on empty linked list.");
  Node* node_to_delete = sentinel_.prev_;
  node_to_delete->prev_->next_ = &sentinel_;
  sentinel_.prev_ = node_to_delete->prev_;
  delete node_to_delete;
  --size_;
}

template<typename T>
void DoublyLinkedList<T>::PopFront() {
  assert(size_ > 0 && "PopFront on empty linked list.");
  Node* node_to_delete = sentinel_.next_;
  node_to_delete->next_->prev_ = &sentinel_;
  sentinel_.next_ = node_to_delete->next_;
  delete node_to_delete;
  --size_;
}

template<typename T>
T& DoublyLinkedList<T>::Back() {
  assert(size_ > 0 && "Back on empty linked list.");
  return sentinel_.prev_->data_;
}
template<typename T>
T& DoublyLinkedList<T>::Front() {
  assert(size_ > 0 && "Front on empty linked list.");
  return sentinel_.next_->data_;
}

template<typename T>
const T& DoublyLinkedList<T>::Back() const {
  assert(size_ > 0 && "Back on empty linked list.");
  return sentinel_.prev_->data_;
}
template<typename T>
const T& DoublyLinkedList<T>::Front() const {
  assert(size_ > 0 && "Front on empty linked list.");
  return sentinel_.next_->data_;
}

template<typename T>
size_t DoublyLinkedList<T>::Size() const {
  return size_;
}

template<typename T>
bool DoublyLinkedList<T>::Empty() const {
  return size_ == 0;
}

template<typename T>
void DoublyLinkedList<T>::Clear() {
  while (!Empty())
    PopFront();
  size_ = 0;
}

template<typename T>
bool DoublyLinkedList<T>::operator==(const DoublyLinkedList& other) const {
  if (this == &other)
    return true;
  if (size_ != other.size_)
    return false;

  Node* this_current = sentinel_.next_;
  Node* other_current = other.sentinel_.next_;
  for (size_t i = 0; i < size_; ++i) {
    if (this_current->data_ != other_current->data_)
      return false;
    this_current = this_current->next_;
    other_current = other_current->next_;
  }

  return true;
}

template<typename T>
bool DoublyLinkedList<T>::operator!=(const DoublyLinkedList& other) const {
  return !(*this == other);
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const DoublyLinkedList& other) {
  if (size_ == 0)
    return *this = other;
  if (!other.Empty()) {
    Node* last = sentinel_.prev_;
    Node* other_current = other.sentinel_.next_;
    while (other_current != nullptr) {
      Node* node = new Node(other_current->data_);
      node->prev_ = last;
      last->next_ = node;
      last = last->next_;
      other_current = other_current->next_;
      ++size_;
    }
    last->next_ = &sentinel_;
    sentinel_.prev_ = last;
  }
  return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const T& val) {
  PushBack(val);
  return *this;
}

#endif //CYCLIC_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H
