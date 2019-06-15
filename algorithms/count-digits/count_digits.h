#ifndef COUNT_DIGITS_COUNT_DIGITS_H
#define COUNT_DIGITS_COUNT_DIGITS_H

#include <cmath>

template<typename T>
unsigned CountDigitsRec(T n) {
  return n >= 0 && n <= 9 ? 1 : CountDigitsRec(n / 10) + 1;
}

template<typename T>
unsigned CountDigitsIter(T n) {
  unsigned counter = 0;
  do {
    ++counter;
    n /= 10;
  } while (n > 0);

  return counter;
}

template<typename T>
unsigned CountDigitsLog(T n) {
  return static_cast<unsigned>(log10(n) + 1);
}

#endif //COUNT_DIGITS_COUNT_DIGITS_H
