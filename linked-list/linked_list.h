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

  typename LinkedList<T>::Node* GetLastNode() const;
  void Copy(const LinkedList&);
 public:
  LinkedList();
  LinkedList(const LinkedList&);
  ~LinkedList();
  LinkedList& operator=(const LinkedList&);

  bool operator==(const LinkedList<T>& other) const;
  bool operator!=(const LinkedList<T>& other) const;

  LinkedList<T>& operator+=(const LinkedList<T>& other);
  LinkedList<T>& operator+=(const T& val);

  bool Empty() const;
  size_t Size() const;

  void PushFront(const T&);
  void PopFront();

  void PushBack(const T&);
  void PopBack();

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
typename LinkedList<T>::Node* LinkedList<T>::GetLastNode() const {
  Node* current = head_;
  while (current->next_ != nullptr)
    current = current->next_;
  return current;
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
void LinkedList<T>::PushBack(const T& val) {
  if (Empty()) {
    head_ = new Node(val);
    head_->next_ = nullptr;
  } else {
    Node* last = GetLastNode();
    last->next_ = new Node(val);
    last->next_->next_ = nullptr;
  }
  ++size_;
}

template<typename T>
void LinkedList<T>::PopBack() {
  assert(!Empty() && "Pop method called on empty list");
  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
  } else {
    Node* current = head_;
    do current = current->next_;
    while (current->next_ != nullptr);
    delete current->next_;
    current->next_ = nullptr;
  }
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
  return GetLastNode()->val_;
}

template<typename T>
void LinkedList<T>::Clear() {
  while (!Empty())
    PopFront();
  delete head_;
  size_ = 0;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& other) {
  if (!other.Empty()) {
    Node* last = GetLastNode();
    Node* other_current = other.head_;

    while (other_current != nullptr) {
      last->next_ = new Node(other_current->val_);
      last = last->next_;
      other_current = other_current->next_;
      ++size_;
    }
    last->next_ = nullptr;
  }

  return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator+=(const T& val) {
  PushBack(val);
  return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const {
  if (this == &other)
    return true;
  if (size_ != other.size_)
    return false;

  Node* this_current = head_;
  Node* other_current = other.head_;
  for (size_t i = 0; i < size_; ++i) {
    if (this_current->val_ != other_current->val_)
      return false;
    this_current = this_current->next_;
    other_current = other_current->next_;
  }

  return true;
}

template<typename T>
bool LinkedList<T>::operator!=(const LinkedList<T>& other) const {
  return !(*this == other);
}

#endif //LINKEDLIST_LINKEDLIST_H
