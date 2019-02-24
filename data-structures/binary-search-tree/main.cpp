#include <iostream>
#include "binary_search_tree.h"

using namespace std;

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

  const auto walk_callback = [](const int& data) { cout << data << " ";};
  bst.PreOrderWalk(walk_callback); cout << endl;
  bst.InOrderWalk(walk_callback); cout << endl;
  bst.PostOrderWalk(walk_callback); cout << endl;

  bst.Remove(3);
  bst.InOrderWalk(walk_callback); cout << endl;

  bst.Remove(8);
  bst.InOrderWalk(walk_callback); cout << endl;

  assert(bst.Contains(8) == false && "8 should be deleted");
  assert(bst.Empty() == false && "bst should not be empty");
  assert(bst.Min() == 1 && "min element should be 1");
  assert(bst.Max() == 14 && "max element should be 14");

  bst.Insert(100000);
  assert(bst.Max() > 20 && "max element should be > 20");
  
  return 0;
}