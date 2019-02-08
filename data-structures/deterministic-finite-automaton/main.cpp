#include <iostream>
#include <string>
#include "dfa.h"

using namespace std;

void test(const std::string& str, const char* txt, DFA<int>& dfa) {
  cout << str << txt << (dfa(str) ? "true" : "false") << endl;
}

int main() {
  DFA<int> dfa;
  std::cout << dfa.AddState(0, true);
  std::cout << dfa.AddState(1);
  std::cout << dfa.AddTransition(0, '0', 1);
  std::cout << dfa.AddTransition(0, '1', 0);
  std::cout << dfa.AddTransition(1, '1', 1);
  std::cout << dfa.AddTransition(1, '0', 0);

  std::cout << "\nstates: " << dfa.StatesCount() << ", finals: " << dfa.FinalStatesCount() << std::endl;

  const char* descr = " contains even number of zeros? : ";
  test("10", descr, dfa);
  test("100", descr, dfa);
  test("1000", descr, dfa);
  test("1110110", descr, dfa);
  test("110011", descr, dfa);

  std::cout << dfa.RemoveState(1);
  std::cout << dfa.AddState(1);
  std::cout << dfa.RemoveTransition(0, 1);
  std::cout << dfa.RemoveTransition(0, '0');
  std::cout << dfa.RemoveTransition(0, 0);
  std::cout << dfa.RemoveTransition(0, '1');

  return 0;
}