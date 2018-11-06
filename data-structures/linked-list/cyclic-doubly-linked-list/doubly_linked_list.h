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
    Node* next;
    Node* prev_;
    explicit Node(T data);
  } sentinel_;
  size_t size_;
  void CopyList(const DoublyLinkedList&);
 public:
  DoublyLinkedList();
  ~DoublyLinkedList();

  DoublyLinkedList(const DoublyLinkedList&);
  DoublyLinkedList& operator=(const DoublyLinkedList&);

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
  Node* o_current = other.sentinel_.next;
  while (o_current != &other.sentinel_) {
    PushBack(o_current->data_);
    o_current = o_current->next;
  }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : sentinel_(Node()), size_(0) {
  sentinel_.prev_ = sentinel_.next = &sentinel_;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Clear();
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other)
    : sentinel_(Node()), size_(0) {
  sentinel_.prev_ = sentinel_.next = &sentinel_;
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
  node->next = &sentinel_;
  sentinel_.prev_->next = node;
  sentinel_.prev_ = node;
  ++size_;
}

template<typename T>
void DoublyLinkedList<T>::PushFront(const T& val) {
  Node* node = new Node(val);
  node->next = sentinel_.next;
  node->prev_ = &sentinel_;
  sentinel_.next->prev_ = node;
  sentinel_.next = node;
  ++size_;
}

template<typename T>
void DoublyLinkedList<T>::PopBack() {
  assert(size_ > 0 && "PopBack on empty linked list.");
  Node* node_to_delete = sentinel_.prev_;
  node_to_delete->prev_->next = &sentinel_;
  sentinel_.prev_ = node_to_delete->prev_;
  delete node_to_delete;
  --size_;
}

template<typename T>
void DoublyLinkedList<T>::PopFront() {
  assert(size_ > 0 && "PopFront on empty linked list.");
  Node* node_to_delete = sentinel_.next;
  node_to_delete->next->prev_ = &sentinel_;
  sentinel_.next = node_to_delete->next;
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
  return sentinel_.next->data_;
}

template<typename T>
const T& DoublyLinkedList<T>::Back() const {
  assert(size_ > 0 && "Back on empty linked list.");
  return sentinel_.prev_->data_;
}
template<typename T>
const T& DoublyLinkedList<T>::Front() const {
  assert(size_ > 0 && "Front on empty linked list.");
  return sentinel_.next->data_;
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

#endif //CYCLIC_DOUBLY_LINKED_LIST_DOUBLY_LINKED_LIST_H
