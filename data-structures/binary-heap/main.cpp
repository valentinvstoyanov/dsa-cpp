#include <iostream>
#include "binary_heap.h"

int main() {
  std::vector<int> v1 = {1, 2, 10, 20, 1000, 0, 4, 800};

  for (int& item: v1)
    std::cout << item << " ";
  std::cout << '\n';

  BinaryHeap<int> h1(v1);

  std::cout << "Top: " << h1.Top() << "\n";

  int insert_val1 = 2000;
  std::cout << "Insert: " << insert_val1 << "\n";
  h1.Insert(insert_val1);

  std::cout << "Extract: " << h1.Extract() << "\n";
  std::cout << "Top: " << h1.Top() << "\n";

  int insert_val2 = 500;
  std::cout << "Insert: " << insert_val2 << "\n";
  h1.Insert(insert_val2);

  std::cout << "Before update Top: " << h1.Top() << "\n";
  h1.UpdateKey(0, 1001);
  std::cout << "After update Top: " << h1.Top() << "\n";

  std::cout << "Before update(last) Top: " << h1.Top() << "\n";
  h1.UpdateKey(h1.Size() - 1, 10002);
  std::cout << "After update(last) Top: " << h1.Top() << "\n";

  while (!h1.IsEmpty())
    std::cout << "Extract: " << h1.Extract() << "\n";

  BinaryHeap<int, std::greater<>> h2({5, 4, 3, 2});
  std::cout << "Top: " << h2.Top() << "\n";
  h2.UpdateKey(0, 2);
  std::cout << "Top: " << h2.Top() << "\n";


  return 0;
}