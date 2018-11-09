//
// Created by valio_stoyanov on 10/18/18.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <cstddef>

template<typename T>
class SinglyLinkedList {
  struct Node {
    T val_;
    Node* next_;
    explicit Node(const T& val)
        : val_(val) {};
  };

  Node* head_;
  size_t size_;

  typename SinglyLinkedList<T>::Node* GetLastNode() const;
  void CopyLinkedList(const SinglyLinkedList&);
 public:
  SinglyLinkedList();
  SinglyLinkedList(const SinglyLinkedList&);
  ~SinglyLinkedList();
  SinglyLinkedList& operator=(const SinglyLinkedList&);

  bool operator==(const SinglyLinkedList<T>& other) const;
  bool operator!=(const SinglyLinkedList<T>& other) const;

  SinglyLinkedList<T>& operator+=(const SinglyLinkedList<T>& other);
  SinglyLinkedList<T>& operator+=(const T& val);

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
SinglyLinkedList<T>::SinglyLinkedList()
    : head_(nullptr), size_(0) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  Clear();
}

template<typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::GetLastNode() const {
  Node* current = head_;
  while (current->next_ != nullptr)
    current = current->next_;
  return current;
}

template<typename T>
void SinglyLinkedList<T>::CopyLinkedList(const SinglyLinkedList& other) {
  if (other.Empty())
    return;

  Node* other_current = other.head_->next_;
  PushFront(other.head_->val_);
  Node* this_current = head_;
  while (other_current != nullptr) {
    this_current->next_ = new Node(other_current->val_);
    other_current = other_current->next_;
    this_current = this_current->next_;
    ++size_;
  }
  this_current->next_ = nullptr;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other)
    : head_(nullptr), size_(0) {
  CopyLinkedList(other);
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other) {
  if (this != &other) {
    Clear();
    CopyLinkedList(other);
  }

  return *this;
}

template<typename T>
bool SinglyLinkedList<T>::Empty() const {
  return size_ == 0;
}

template<typename T>
size_t SinglyLinkedList<T>::Size() const {
  return size_;
}

template<typename T>
void SinglyLinkedList<T>::PushFront(const T& val) {
  Node* new_head = new Node(val);
  new_head->next_ = head_;
  head_ = new_head;
  ++size_;
}

template<typename T>
void SinglyLinkedList<T>::PopFront() {
  assert(!Empty() && "Pop method called on empty list");
  Node* new_head = head_->next_;
  delete head_;
  head_ = new_head;
  --size_;
}

template<typename T>
void SinglyLinkedList<T>::PushBack(const T& val) {
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
void SinglyLinkedList<T>::PopBack() {
  assert(!Empty() && "Pop method called on empty list");
  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
  } else {
    Node* current = head_;
    while (current->next_->next_ != nullptr)
      current = current->next_;
    delete current->next_;
    current->next_ = nullptr;
  }
  --size_;
}

template<typename T>
const T& SinglyLinkedList<T>::Front() const {
  assert(!Empty() && "Front method called on empty list");
  return head_->val_;
}

template<typename T>
const T& SinglyLinkedList<T>::Back() const {
  assert(!Empty() && "Back method called on empty list");
  return GetLastNode()->val_;
}

template<typename T>
void SinglyLinkedList<T>::Clear() {
  while (!Empty())
    PopFront();
  delete head_;
  head_ = nullptr;
  size_ = 0;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+=(const SinglyLinkedList<T>& other) {
  if (size_ == 0)
    return *this = other;
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
SinglyLinkedList<T>& SinglyLinkedList<T>::operator+=(const T& val) {
  PushBack(val);
  return *this;
}

template<typename T>
bool SinglyLinkedList<T>::operator==(const SinglyLinkedList<T>& other) const {
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
bool SinglyLinkedList<T>::operator!=(const SinglyLinkedList<T>& other) const {
  return !(*this == other);
}

#endif //LINKEDLIST_LINKEDLIST_H
