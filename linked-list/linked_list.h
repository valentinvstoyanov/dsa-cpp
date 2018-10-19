//
// Created by valio_stoyanov on 10/18/18.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <cstddef>
template<typename T>
class LinkedList {
  struct Node {
    T val_;
    Node* next_;
    Node(const T& val)
        : val_(val) {};
  };

  Node* head_;
  size_t size_;
  void Copy(const LinkedList&);
 public:
  LinkedList();
  LinkedList(const LinkedList&);
  ~LinkedList();
  LinkedList& operator=(const LinkedList&);

  bool Empty() const;
  size_t Size() const;

  void PushFront(const T&);
  void PopFront();

  const T& Front() const;
  const T& Back() const;

  void Clear();
};

template<typename T>
LinkedList<T>::LinkedList()
    : head_(nullptr), size_(0) {}

template<typename T>
LinkedList<T>::~LinkedList() {
  Clear();
}

template<typename T>
void LinkedList<T>::Copy(const LinkedList& other) {
  if (other.Empty())
    return;

  Node* other_current = other.head_->next_;
  Node* this_current = new Node(other.head_->val_);
  head_ = this_current;
  ++size_;
  while (other_current != nullptr) {
    this_current->next_ = new Node(other_current->val_);
    other_current = other_current->next_;
    this_current = this_current->next_;
    ++size_;
  }
  this_current->next_ = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    : head_(nullptr), size_(0) {
  Copy(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
  if (this != &other) {
    Clear();
    Copy(other);
  }

  return *this;
}

template<typename T>
bool LinkedList<T>::Empty() const {
  return size_ == 0;
}

template<typename T>
size_t LinkedList<T>::Size() const {
  return size_;
}

template<typename T>
void LinkedList<T>::PushFront(const T& val) {
  Node* new_head = new Node(val);
  new_head->next_ = head_;
  head_ = new_head;
  ++size_;
}

template<typename T>
void LinkedList<T>::PopFront() {
  assert(!Empty() && "Pop method called on empty list");
  Node* new_head = head_->next_;
  delete head_;
  head_ = new_head;
  --size_;
}

template<typename T>
const T& LinkedList<T>::Front() const {
  assert(!Empty() && "Front method called on empty list");
  return head_->val_;
}

template<typename T>
const T& LinkedList<T>::Back() const {
  assert(!Empty() && "Back method called on empty list");
  Node* current = head_;
  while (current->next_ != nullptr)
    current = current->next_;
  return current->val_;
}

template<typename T>
void LinkedList<T>::Clear() {
  while (!Empty())
    PopFront();
  delete head_;
  size_ = 0;
}

#endif //LINKEDLIST_LINKEDLIST_H
