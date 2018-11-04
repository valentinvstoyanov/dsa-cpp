//
// Created by valio_stoyanov on 11/4/18.
//

#ifndef BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H

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
  BST ToBST(Node*) const;
 public:
  BST();
  ~BST();

  BST(const BST&);
  BST& operator=(const BST&);

  BST Search(const T&) const;
};

template<typename T>
BST<T>::Node::Node(T data)
    : data_(data), left_(nullptr), right_(nullptr) {}

template<typename T>
BST<T>::BST()
    : root_(nullptr) {}

template<typename T>
BST<T>::~BST() {
  //TODO
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
  if (node == nullptr) return nullptr;
  if (node->data_ == x) return node;
  if (x < node->data_) return Search(node->left_, x);
  else return Search(node->right_, x);
}

template<typename T>
BST<T> BST<T>::Search(const T& x) const {
  return ToBST(Search(root_, x));
}

template<typename T>
BST<T> BST<T>::ToBST(BST::Node* node) const {
  //TODO
  return BST();
}

#endif //BINARY_SEARCH_TREE_BINARY_SEARCH_TREE_H
