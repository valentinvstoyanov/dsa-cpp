#include <iostream>
#include "mode.h"

int main() {
  int arr1[10] = {3, 2, 5, 4, 3, 2, 12, 20, 100, 3};
  printf("%d\n", Mode(arr1, 10));
  printf("%d\n", Mode(arr1, 0));

  printf("%d\n", Mode<int>(nullptr, 10));

  int arr2[1] = {1};
  printf("%d\n", Mode(arr2, 1));

  int arr3[5] = {1, 2, 3, 4, 5};
  printf("%d\n", Mode(arr3, 5));

  int arr4[5] = {1, 1, 1, 1, 1};
  printf("%d\n", Mode(arr4, 5));

  int arr5[6] = {2, 2, 3, 3, 2, 3};
  printf("%d\n", Mode(arr5, 6));

  return 0;
}