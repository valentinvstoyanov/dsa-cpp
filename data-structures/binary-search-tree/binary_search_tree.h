//
// Created by valio_stoyanov on 11/4/18.
//

#ifndef BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H

#include <cassert>
#include <vector>

template<typename T>
class BST {
  struct Node {
    T data_;
    Node* left_;
    Node* right_;
    explicit Node(T data);
  };
  Node* root_;

  Node* Search(Node*, const T&) const;
  void Insert(Node*, Node*, const T&);
  void Clear(Node*);
  void PreOrder(Node*, std::vector<T>&) const;
  void InOrder(Node*, std::vector<T>&) const;
  void PostOrder(Node*, std::vector<T>&) const;
 public:
  BST();
  ~BST();

  BST(const BST&);
  BST& operator=(const BST&);

  bool Empty() const;
  bool Contains(const T&) const;

  const T& Min() const;
  const T& Max() const;
  T& Min();
  T& Max();

  void Insert(const T&);

  void Clear();

  std::vector<T> PreOrder() const;
  std::vector<T> InOrder() const;
  std::vector<T> PostOrder() const;
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

  }
  return *this;
}

template<typename T>
typename BST<T>::Node* BST<T>::Search(BST::Node* node, const T&  x) const {
  if (!node) return nullptr;
  if (node->data_ == x) return node;
  if (x < node->data_) return Search(node->left_, x);
  else return Search(node->right_, x);
}

template<typename T>
bool BST<T>::Empty() const {
  return !root_;
}

template<typename T>
bool BST<T>::Contains(const T& x) const {
  return Search(root_, x);
}

template<typename T>
const T& BST<T>::Min() const {
  assert(root_ && "Min called on empty BST");
  Node* min = root_;
  while (min->left_) min = min->left_;
  return min->data_;
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
void BST<T>::Insert(BST::Node* parent, BST::Node* current, const T& data) {
  if (!current) {
    current = new Node(data);
    if (!parent) root_ = current;
    else if (parent->left_) parent->right_ = current;
    else parent->left_ = current;
    return;
  }
  if (data < current->data_) Insert(current, current->left_, data);
  else Insert(current, current->right_, data);
}

template<typename T>
void BST<T>::Insert(const T& data) {
  Insert(nullptr, root_, data);
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
void BST<T>::PreOrder(BST::Node* node, std::vector<T>& res) const {
  if (!node) return;
  res.push_back(node->data_);
  PreOrder(node->left_, res);
  PreOrder(node->right_, res);
}

template<typename T>
void BST<T>::InOrder(BST::Node* node, std::vector<T>& res) const {
  if (!node) return;
  InOrder(node->left_, res);
  res.push_back(node->data_);
  InOrder(node->right_, res);
}

template<typename T>
void BST<T>::PostOrder(BST::Node* node, std::vector<T>& res) const {
  if (!node) return;
  PostOrder(node->left_, res);
  PostOrder(node->right_, res);
  res.push_back(node->data_);
}

template<typename T>
std::vector<T> BST<T>::PreOrder() const {
  std::vector<T> result;
  PreOrder(root_, result);
  return result;
}

template<typename T>
std::vector<T> BST<T>::InOrder() const {
  std::vector<T> result;
  InOrder(root_, result);
  return result;
}

template<typename T>
std::vector<T> BST<T>::PostOrder() const {
  std::vector<T> result;
  PostOrder(root_, result);
  return result;
}


#endif //BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
