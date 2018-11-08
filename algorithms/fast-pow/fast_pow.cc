//
// Created by valio_stoyanov on 11/8/18.
//

#include "fast_pow.h"

long long FastPow(long long a, unsigned long long n) {
  if (n == 0) return 1;
  long long x = FastPow(a, n / 2);
  if (n % 2 == 0) return x * x;
  else return a * x * x;
}