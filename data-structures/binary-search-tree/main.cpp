#include <iostream>
#include "binary_search_tree.h"

using namespace std;

template<typename T>
void PrintVector(const vector<T>& v, const string& str) {
  cout << str << ": ";
  for (size_t i = 0; i < v.size(); ++i)
    cout << v[i] << ' ';
  cout << endl;
}

int main() {
  BST<int> bst;
  bst.Insert(8);
  bst.Insert(3);
  bst.Insert(10);
  bst.Insert(1);
  bst.Insert(6);
  bst.Insert(7);
  bst.Insert(4);
  bst.Insert(14);
  bst.Insert(13);

  PrintVector(bst.PreOrder(), "Pre-order: ");
  PrintVector(bst.InOrder(), "In-order: ");
  PrintVector(bst.PostOrder(), "Post-order: ");


  return 0;
}