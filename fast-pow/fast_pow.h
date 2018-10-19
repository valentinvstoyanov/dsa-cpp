//
// Created by valio_stoyanov on 10/19/18.
//

#ifndef FAST_POW_FAST_POW_H
#define FAST_POW_FAST_POW_H

long long fast_pow(long long a, long long n) {
  if (n == 0) return 1;
  long long x = fast_pow(a, n / 2);
  if (n % 2 == 0) return x * x;
  else return a * x * x;
}

#endif //FAST_POW_FAST_POW_H
