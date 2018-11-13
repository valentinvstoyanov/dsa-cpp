#include <iostream>
#include <string>
#include <vector>
#include "dfa.h"

using namespace std;

template <typename T, typename S>
void test(vector<T> v, const char* txt, DFA<T, S>& dfa) {
  for (auto& e: v) cout << e;
  cout << txt << (dfa(v) ? "true" : "false") << ", current state: " << dfa.CurrentState() << endl;
  dfa.Clear();
}

int main() {
  DFA<int, string> dfa1("q1", true);
  dfa1.AddState("q2");
  dfa1.AddTransition("q1", 1, "q1");
  dfa1.AddTransition("q1", 0, "q2");
  dfa1.AddTransition("q2", 1, "q2");
  dfa1.AddTransition("q2", 0, "q1");

  const char* descr = " contains even number of zeros? : ";
  test({1, 0}, descr, dfa1);
  test({1, 0, 0}, descr, dfa1);
  test({1, 0, 0, 0}, descr, dfa1);
  test({1, 1, 1, 0, 1, 1, 0}, descr, dfa1);
  test({1, 1, 0, 0, 1, 1}, descr, dfa1);

  return 0;
}