#include <iostream>
#include <array>
#include "longest_increasing_subsequence.h"

int main() {
  std::array<int, 7> s1 = {3, 4, -1, 0, 6, 2, 3};
  std::array<int, 6> s2 = {3, 5, 6, 2, 3, 7};
  std::array<int, 5> s3 = {3, -10, 10, -5, 20};
  std::cout << LIS(s1.data(), s1.size()) << std::endl;
  std::cout << LIS(s2.data(), s2.size()) << std::endl;
  std::cout << LIS(s3.data(), s3.size()) << std::endl;
  return 0;
}
