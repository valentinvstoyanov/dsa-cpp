//
// Created by valio_stoyanov on 11/7/18.
//

#include <cassert>
#include "gcd_lcm.h"

long long GCD(long long a, long long b) {
  return b == 0 ? a : GCD(b, a % b);
}

long long LCM(long long a, long long b) {
  return (a * b) / GCD(a, b);
}

long long GCD(const long long* arr, size_t size) {
  assert((arr && size >= 2) && "GCD: cannot be applied to array with less than 2 element");
  if (size == 2) return GCD(arr[0], arr[1]);
  return GCD(GCD(arr, size - 1), arr[size - 1]);
}

long long LCM(const long long* arr, size_t size) {
  assert((arr && size >= 2) && "LCM: cannot be applied to array with less than 2 element");
  if (size == 2) return LCM(arr[0], arr[1]);
  return LCM(LCM(arr, size - 1), arr[size - 1]);
}