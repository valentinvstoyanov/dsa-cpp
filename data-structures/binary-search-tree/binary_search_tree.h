//
// Created by valio_stoyanov on 11/4/18.
//

#ifndef BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H

#include <cassert>
#include <vector>
#include <functional>

template<typename T>
class BST {
 public:
  using WalkCallback = std::function<void(const T&)>;
 private:

  struct Node {
    T data_;
    Node* left_;
    Node* right_;
    explicit Node(T data);
  };
  Node* root_;

  Node** SearchMin(Node** root) const;
  Node** Search(const T&);

  void Clear(Node*);
  void PreOrderWalk(Node*, const WalkCallback&) const;
  void InOrderWalk(Node*, const WalkCallback&) const;
  void PostOrderWalk(Node*, const WalkCallback&) const;
 public:
  BST();
  ~BST();

  BST(const BST&);
  BST& operator=(const BST&);

  bool Empty() const;
  bool Contains(const T&);

  const T& Min() const;
  const T& Max() const;
  T& Min();
  T& Max();

  void Insert(const T&);
  void Remove(const T&);

  void Clear();

  void PreOrderWalk(const WalkCallback&) const;
  void InOrderWalk(const WalkCallback&) const;
  void PostOrderWalk(const WalkCallback&) const;
};

template<typename T>
BST<T>::Node::Node(T data)
    : data_(data), left_(nullptr), right_(nullptr) {}

template<typename T>
BST<T>::BST()
    : root_(nullptr) {}

template<typename T>
BST<T>::~BST() {
  Clear();
}

template<typename T>
BST<T>::BST(const BST&) {
  //TODO
}

template<typename T>
BST<T>& BST<T>::operator=(const BST& other) {
  if (this != &other) {
    //TODO
  }
  return *this;
}

template<typename T>
typename BST<T>::Node** BST<T>::SearchMin(Node** root) const {
  Node** node = root;
  while (*node && (*node)->left_)
    node = &(*node)->left_;

  return node;
}

template<typename T>
typename BST<T>::Node** BST<T>::Search(const T& x) {
  Node** node = &root_;
  while (*node) {
    if ((*node)->data_ == x)
      return node;
    node = x < (*node)->data_ ? &(*node)->left_ : &(*node)->right_;
  }

  return node;
}

template<typename T>
bool BST<T>::Empty() const {
  return !root_;
}

template<typename T>
bool BST<T>::Contains(const T& x) {
  return *Search(x);
}

template<typename T>
const T& BST<T>::Min() const {
  assert(root_ && "Min called on empty BST");
  return (*SearchMin(&root_))->data_;
}

template<typename T>
const T& BST<T>::Max() const {
  assert(root_ && "Max called on empty BST");
  Node* max = root_;
  while (max->right_) max = max->right_;
  return max->data_;
}

template<typename T>
T& BST<T>::Min() {
  assert(root_ && "Min called on empty BST");
  Node* min = root_;
  while (min->left_) min = min->left_;
  return min->data_;
}

template<typename T>
T& BST<T>::Max() {
  assert(root_ && "Max called on empty BST");
  Node* max = root_;
  while (max->right_) max = max->right_;
  return max->data_;
}

template<typename T>
void BST<T>::Insert(const T& data) {
  Node** result = Search(data);
  assert(*result == nullptr && "Attempt to insert value that is already in the BST");
  *result = new Node(data);
}

template<typename T>
void BST<T>::Remove(const T& data) {
  Node** node = Search(data);
  if (!*node) return;

  Node* node_to_delete = *node;
  if (node_to_delete->left_ && node_to_delete->right_) {
    Node** min = SearchMin(&node_to_delete->right_);
    *node = *min;
    (*min) = (*min)->right_;
    (*node)->left_ = node_to_delete->left_;
    (*node)->right_ = node_to_delete->right_;
  } else {
    *node = (*node)->left_ ? (*node)->left_ : (*node)->right_;
  }

  delete node_to_delete;
}

template<typename T>
void BST<T>::Clear(BST::Node* node) {
  if (!node) return;
  Clear(node->left_);
  Clear(node->right_);
  delete node;
}

template<typename T>
void BST<T>::Clear() {
  Clear(root_);
  root_ = nullptr;
}

template<typename T>
void BST<T>::PreOrderWalk(BST::Node* node, const WalkCallback& callback) const {
  if (!node) return;
  callback(node->data_);
  PreOrderWalk(node->left_, callback);
  PreOrderWalk(node->right_, callback);
}

template<typename T>
void BST<T>::InOrderWalk(BST::Node* node, const WalkCallback& callback) const {
  if (!node) return;
  InOrderWalk(node->left_, callback);
  callback(node->data_);
  InOrderWalk(node->right_, callback);
}

template<typename T>
void BST<T>::PostOrderWalk(BST::Node* node, const WalkCallback& callback) const {
  if (!node) return;
  PostOrderWalk(node->left_, callback);
  PostOrderWalk(node->right_, callback);
  callback(node->data_);
}

template<typename T>
void BST<T>::PreOrderWalk(const WalkCallback& callback) const {
  PreOrderWalk(root_, callback);
}

template<typename T>
void BST<T>::InOrderWalk(const WalkCallback& callback) const {
  InOrderWalk(root_, callback);
}

template<typename T>
void BST<T>::PostOrderWalk(const WalkCallback& callback) const {
  PostOrderWalk(root_, callback);
}

#endif //BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
