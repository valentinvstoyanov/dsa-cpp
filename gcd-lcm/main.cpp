#include <iostream>

int GCD(int a, int b) {
  return b == 0 ? a : GCD(b, a % b);
}

int LCM(int a, int b) {
  return (a * b) / GCD(a, b);
}

int main() {
  std::cout << GCD(36, 108) << ", " << LCM(4, 6) << std::endl;
  return 0;
}