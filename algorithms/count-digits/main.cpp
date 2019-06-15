#include <iostream>
#include "count_digits.h"

int main() {
  std::cout << CountDigitsIter(654534) << ' ' << CountDigitsRec(654534) << ' ' << CountDigitsLog(654534) << std::endl;
  std::cout << CountDigitsIter(0) << ' ' << CountDigitsRec(0) << ' ' << CountDigitsLog(0) << std::endl;
  std::cout << CountDigitsIter(1) << ' ' << CountDigitsRec(1) << ' ' << CountDigitsLog(1) << std::endl;
  std::cout << CountDigitsIter(17) << ' ' << CountDigitsRec(17) << ' ' << CountDigitsLog(17) << std::endl;
  return 0;
}