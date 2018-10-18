#include <iostream>
#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "DynamicArray.h"

TEST_CASE( "DynamicArray with default ctor", "[DynamicArray]" ) {
  DynamicArray<int> arr;
  REQUIRE(arr.Size() == 0);
  REQUIRE(arr.Capacity() == 1);
  REQUIRE(arr.Empty());
}

TEST_CASE( "DynamicArray with initial capacity", "[DynamicArray]" ) {
  DynamicArray<int> arr(100);
  REQUIRE(arr.Size() == 0);
  REQUIRE(arr.Capacity() == 100);
  REQUIRE(arr.Empty());
}

TEST_CASE( "DynamicArray push back 10 elements back", "[DynamicArray]" ) {
  DynamicArray<int> arr(0);

  for (unsigned i = 0; i < 10; ++i)
    arr.PushBack(i);
  REQUIRE(arr.Front() == 0);
  REQUIRE(arr.Size() == 10);
  REQUIRE(arr.Capacity() == 16);
}

TEST_CASE( "DynamicArray pop back 10 elements", "[DynamicArray]" ) {
  DynamicArray<int> arr;

  for (unsigned i = 0; i < 10; ++i)
    arr.PushBack(i);

  for (unsigned i = 0; i < 10; ++i)
    arr.PopBack();
  REQUIRE(arr.Size() == 0);
  REQUIRE(arr.Capacity() == 16);
}

TEST_CASE( "DynamicArray can show it's k-th element through operator[]", "[DynamicArray]" ) {
  DynamicArray<int> arr;
  for (unsigned i = 0; i < 10; ++i) {
    arr.PushBack(i);
    REQUIRE(arr[i] == i);
  }
}

TEST_CASE( "DynamicArray can show it's k-th element", "[DynamicArray]" ) {
  DynamicArray<int> arr;
  for (unsigned i = 0; i < 10; ++i) {
    arr.PushBack(i);
    REQUIRE(arr.At(i) == i);
  }
}

TEST_CASE( "DynamicArray can show it's first and last element", "[DynamicArray]" ) {
  DynamicArray<int> arr;

  SECTION( "10 elements" ) {
    for (unsigned i = 0; i < 10; ++i)
      arr.PushBack(i);
    REQUIRE(arr.Front() == 0);
    REQUIRE(arr.Back() == 9);
  }

  SECTION( "Single element" ) {
    arr.PushBack(1000);
    REQUIRE(arr.Front() == 1000);
    REQUIRE(arr.Back() == 1000);
  }
}

TEST_CASE( "DynamicArray can be cleared", "[DynamicArray]" ) {
  DynamicArray<int> arr(0);

  SECTION( "On empty array with zero capacity" ) {
    arr.Clear();
    REQUIRE(arr.Empty());
    REQUIRE(arr.Size() == 0);
    REQUIRE(arr.Capacity() == 0);
  }

  SECTION( "On non-empty array" ) {
    for (unsigned i = 0; i < 10; ++i)
      arr.PushBack(i + 1000);

    arr.Clear();
    REQUIRE(arr.Empty());
    REQUIRE(arr.Size() == 0);
    REQUIRE(arr.Capacity() == 0);
  }

  SECTION( "On empty array" ) {
    arr.Clear();
    REQUIRE(arr.Empty());
    REQUIRE(arr.Size() == 0);
    REQUIRE(arr.Capacity() == 0);
  }
}

TEST_CASE( "DynamicArray can be shrinked to fit size", "[DynamicArray]" ) {
  SECTION( "On empty array with zero capacity" ) {
    DynamicArray<int> arr(0);
    arr.ShrinkToFit();
    REQUIRE(arr.Size() == arr.Capacity());
  }

  SECTION( "On empty array with non-zero capacity" ) {
    DynamicArray<int> arr(100);
    arr.ShrinkToFit();
    REQUIRE(arr.Size() == arr.Capacity());
  }

  SECTION( "On non-empty array" ) {
    DynamicArray<int> arr;
    for (unsigned i = 0; i < 100; ++i)
      arr.PushBack(i);
    arr.ShrinkToFit();
    REQUIRE(arr.Size() == arr.Capacity());
  }
}

TEST_CASE( "DynamicArray can reserve capacity", "[DynamicArray]" ) {
  DynamicArray<int> arr;

  SECTION( "On empty array with zero capacity" ) {
    arr.Clear();
    arr.Reserve(100);
    REQUIRE(arr.Capacity() == 100);
  }

  SECTION( "On non-empty array" ) {
    for (unsigned i = 0; i < 10; ++i)
      arr.PushBack(i);
    arr.Reserve(100);
    REQUIRE(arr.Capacity() == 100);
  }

  SECTION( "On empty array with non-zero capacity" ) {
    arr.Reserve(100);
    REQUIRE(arr.Capacity() == 100);
  }
}

TEST_CASE( "DynamicArray copy ctor", "[DynamicArray]" ) {
  DynamicArray<int> arr;

  SECTION( "On empty array" ) {
    DynamicArray<int> arrCopy(arr);
    REQUIRE(arrCopy.Size() == arr.Size());
    REQUIRE(arrCopy.Capacity() == arr.Capacity());
  }

  SECTION( "On empty array with non-zero capacity" ) {
    arr.Clear();
    DynamicArray<int> arrCopy(arr);
    REQUIRE(arrCopy.Size() == arr.Size());
    REQUIRE(arrCopy.Capacity() == arr.Capacity());
  }

  SECTION( "On non-empty array" ) {
    for (unsigned i = 0; i < 10; ++i)
      arr.PushBack(i);
    DynamicArray<int> arrCopy(arr);
    REQUIRE(arrCopy.Size() == arr.Size());
    REQUIRE(arrCopy.Capacity() == arr.Capacity());
    for (unsigned i = 0; i < 10; ++i)
      REQUIRE(arrCopy[i] == arr[i]);
  }
}

TEST_CASE( "DynamicArray operator==", "[DynamicArray]" ) {
  SECTION( "On empty array with non-zero capacity" ) {
    DynamicArray<int> da1;
    DynamicArray<int> da2(0);
    da2 = da1;
    REQUIRE(da2.Size() == da1.Size());
    REQUIRE(da2.Capacity() == da1.Capacity());
  }

  SECTION( "On non-empty array" ) {
    DynamicArray<int> da1;
    DynamicArray<int> da2(0);
    da1.PushBack(10);
    da2.PushBack(110);
    da2 = da1;
    REQUIRE(da2.Size() == da1.Size());
    REQUIRE(da2.Capacity() == da1.Capacity());
    REQUIRE(da2.Front() == da1.Front());
  }
}

TEST_CASE( "DynamicArrays comparison", "[DynamicArray]" ) {
  DynamicArray<int> da1(10);
  DynamicArray<int> da2(10);
  for(unsigned i = 0; i < 10; ++i) {
    da1.PushBack(i);
    da2.PushBack(i);
  }

  REQUIRE(da1 == da2);
  REQUIRE_FALSE(da1 != da2);

  da2.Front() = 1;
  REQUIRE_FALSE(da1 == da2);
  REQUIRE(da1 != da2);

  da1.PopBack();
  REQUIRE_FALSE(da1 == da2);
  REQUIRE(da1 != da2);
}

TEST_CASE( "DynamicArray append other DynamicArray", "[DynamicArray]" ) {
  DynamicArray<int> da1(10);
  DynamicArray<int> da2(10);
  for(unsigned i = 0; i < 10; ++i) {
    da1.PushBack(i);
    da2.PushBack(i + 10);
  }

  da1 += da2;
  REQUIRE(da1.Size() == 20);
  REQUIRE(da1.Back() == 19);
}

TEST_CASE( "DynamicArray append element", "[DynamicArray]" ) {
  DynamicArray<int> arr;
  arr += 1;
  REQUIRE(arr.Size() == 1);
  REQUIRE(arr.Back() == 1);
}

TEST_CASE( "DynamicArray push front 10 elements back", "[DynamicArray]" ) {
  DynamicArray<int> arr(0);

  for (unsigned i = 0; i < 10; ++i)
    arr.PushFront(i);
  REQUIRE(arr.Front() == 9);
  REQUIRE(arr.Size() == 10);
  REQUIRE(arr.Capacity() == 16);
}

TEST_CASE( "DynamicArray pop front 10 elements", "[DynamicArray]" ) {
  DynamicArray<int> arr;

  for (unsigned i = 0; i < 10; ++i)
    arr.PushBack(i);

  for (unsigned i = 0; i < 10; ++i)
    arr.PopFront();
  REQUIRE(arr.Size() == 0);
  REQUIRE(arr.Capacity() == 16);
}