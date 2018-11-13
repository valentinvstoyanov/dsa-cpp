#include <iostream>
#include <string>
#include <vector>
#include "dfa.h"

using namespace std;

template <typename AT, typename ST>
void test(vector<AT> v, const char* txt, DFA<AT, ST>& dfa) {
  for (auto& e: v) cout << e;
  cout << txt << (dfa(v) ? "true" : "false") << ", current state: " << dfa.CurrentState() << endl;
  dfa.Clear();
}

int main() {
  DFA<int, string> dfa1({1, 0}, "q1", true);
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