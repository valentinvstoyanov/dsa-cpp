#include <iostream>
#include <thread>
#include <chrono>
#include "thread_safe_queue.h"

using namespace std::literals::chrono_literals;


int main() {
  ThreadSafeQueue<int> q1;

  std::thread t1([&q1] {
    for (int i = 0; i < 10; ++i) {
	  q1.Push(i);
	  std::this_thread::sleep_for(100ms);
	}
  });

  std::thread t2([&q1] {
	for (int i = 10; i < 20; ++i) {
	  q1.Push(i);
	  std::this_thread::sleep_for(50ms);
	}
  });

  t1.join();
  t2.join();

  std::cout << "queue size = " << q1.Size() << ", empty = " << q1.Empty() << "\n";

  int val;
  while (q1.TryPop(val))
    std::cout << val << " ";
  std::cout << "\n";

  q1.Push(1);
  q1.Clear();
  std::cout << "queue size = " << q1.Size() << ", empty = " << q1.Empty() << "\n";

  ThreadSafeQueue<int> q2(q1);
  q2.Clear();

  std::thread t3([&q2] {
    std::this_thread::sleep_for(500ms);
    for (int i = 0; i < 20; ++i)
      q2.Push(i);
  });

  q2.WaitAndPop(val);
  std::cout << val << "\n";

  t3.join();

  q1 = q2;
  while (q1.TryPop(val)) {
	std::cout << val << "-";
	q2.TryPop(val);
	std::cout << val << "~";
  }
  std::cout << "\n";

  return 0;
}
