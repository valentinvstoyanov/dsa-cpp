#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "dynamic_array.h"
#define DS " DynamicArray "

TEST_CASE(DS "can be created with default ctor", DS) {
  REQUIRE_NOTHROW(DynamicArray<int>());
}

TEST_CASE(DS "can be created with initial capacity", DS) {
  const size_t initial_capacity = 100;
  REQUIRE_NOTHROW(DynamicArray<int>(initial_capacity));
}

TEST_CASE("Empty() returns true on empty" DS, DS) {
  REQUIRE(DynamicArray<char>().Empty());
}

TEST_CASE("Size() returns zero on empty" DS, DS) {
  REQUIRE(DynamicArray<char>().Size() == 0);
}

TEST_CASE("Capacity() returns one when" DS "is created with default ctor", DS) {
  REQUIRE(DynamicArray<char>().Capacity() == 1);
}

TEST_CASE("Clear() should not throw when called on empty" DS, DS) {
  REQUIRE_NOTHROW(DynamicArray<char>().Clear());
}

TEST_CASE("Push elements to" DS "should not throw", DS) {
  DynamicArray<unsigned> ds;
  const unsigned start = 1;
  const unsigned end = 129;

  SECTION("Push front elements") {
    for (unsigned i = start; i <= end; ++i)
      REQUIRE_NOTHROW(ds.PushFront(i));
    REQUIRE_FALSE(ds.Empty());
    REQUIRE(ds.Size() == end - start + 1);
  }
  SECTION("Push back elements") {
    for (unsigned i = start; i <= end; ++i)
      REQUIRE_NOTHROW(ds.PushBack(i));
    REQUIRE(ds.Size() == end - start + 1);
    REQUIRE_FALSE(ds.Empty());
  }
  SECTION("Push front and back elements") {
    for (unsigned i = start; i <= end; ++i)
      if (i > 0 && i % 2 == 0) REQUIRE_NOTHROW(ds.PushBack(i));
      else
        REQUIRE_NOTHROW(ds.PushFront(i));
    REQUIRE(ds.Size() == end - start + 1);
    REQUIRE_FALSE(ds.Empty());
  }
}

TEST_CASE("Pop elements from" DS "should not throw", DS) {
  const int test_arr_size = 5;
  const int test_arr[test_arr_size] = {5, 1, 2, 4, 3};
  DynamicArray<int> ds;
  for (int i = 0; i < test_arr_size; ++i)
    ds.PushBack(test_arr[i]);

  SECTION("Pop back elements") {
    for (int i = 0; i < test_arr_size; ++i) {
      REQUIRE(ds.Back() == test_arr[test_arr_size - i - 1]);
      REQUIRE_NOTHROW(ds.PopBack());
    }
    REQUIRE(ds.Empty());
    REQUIRE(ds.Size() == 0);
  }
  SECTION("Pop front elements") {
    for (int i = 0; i < test_arr_size; ++i)
      REQUIRE_NOTHROW(ds.PopFront());
    REQUIRE(ds.Empty());
    REQUIRE(ds.Size() == 0);
  }
}

TEST_CASE("Front() and Back() should work", DS) {
  DynamicArray<int> ds;
  const unsigned e1 = 0, e2 = 1, e3 = 2;
  ds.PushFront(e1); ds.PushBack(e2); ds.PushBack(e3);
  SECTION("Test Front()") { REQUIRE(ds.Front() == e1); }
  SECTION("Test Back()") { REQUIRE(ds.Back() == e3); }
}

TEST_CASE("At() and operator[] should work", DS) {
  DynamicArray<int> ds;
  const unsigned e1 = 0, e2 = 1, e3 = 2;
  ds.PushFront(e1); ds.PushBack(e2); ds.PushBack(e3);
  SECTION("Test At()") {
    REQUIRE(ds.At(0) == e1);
    REQUIRE(ds.At(1) == e2);
    REQUIRE(ds.At(2) == e3);
  }
  SECTION("Test operator[]") {
    REQUIRE(ds[0] == e1);
    REQUIRE(ds[1] == e2);
    REQUIRE(ds[2] == e3);
  }
}

TEST_CASE("Clear() non-empty" DS, DS) {
  DynamicArray<int> ds;
  const unsigned e1 = 0, e2 = 1, e3 = 2;
  ds.PushFront(e1); ds.PushBack(e2); ds.PushBack(e3);

  SECTION("Once") {
    ds.Clear();
    REQUIRE(ds.Empty());
    REQUIRE(ds.Size() == 0);
    REQUIRE(ds.Capacity() == 0);
  }
  SECTION("More times") {
    for (int i = 0; i < 10; ++i) {
      REQUIRE_NOTHROW(ds.Clear());
      REQUIRE(ds.Empty());
      REQUIRE(ds.Size() == 0);
      REQUIRE(ds.Capacity() == 0);
    }
  }
}

TEST_CASE(DS "comparison", DS) {
  DynamicArray<int> ds1(10);
  DynamicArray<int> ds2(10);

  SECTION("On empty" DS "should be true") {
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with same elements should be true") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.PushBack(i);
      ds2.PushBack(i);
    }
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with different elements should be false") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.PushBack(i);
      ds2.PushBack(i + 10);
    }
    REQUIRE_FALSE(ds1 == ds2);
    REQUIRE(ds1 != ds2);
  }
}

TEST_CASE(DS "can be created with copy ctor", DS) {
  SECTION("From empty" DS) {
    DynamicArray<int> empty_ds;
    DynamicArray<int> ds(empty_ds);
    REQUIRE(ds == empty_ds);
  }
  SECTION("From non-empty" DS) {
    DynamicArray<int> ds;
    const unsigned e1 = 0, e2 = 1, e3 = 2;
    ds.PushFront(e1); ds.PushBack(e2); ds.PushBack(e3);

    DynamicArray<int> copy_of_ds(ds);
    REQUIRE(copy_of_ds == ds);
  }
}

TEST_CASE(DS "operator=", DS) {
  SECTION("On empty" DS) {
    DynamicArray<int> ds1;
    DynamicArray<int> ds2(0);
    ds2 = ds1;
    REQUIRE(ds2 == ds1);
  }
  SECTION("On non-empty" DS) {
    DynamicArray<int> da1;
    DynamicArray<int> da2(0);
    da1.PushBack(10);
    da2.PushBack(110);
    da2 = da1;
    REQUIRE(da2 == da1);
  }
}

TEST_CASE(DS "can be shrinked to fit size", DS) {
  SECTION("On empty array with zero capacity") {
    DynamicArray<int> ds(0);
    ds.ShrinkToFit();
    REQUIRE(ds.Size() == ds.Capacity());
  }
  SECTION("On empty array with non-zero capacity") {
    DynamicArray<int> ds(100);
    ds.ShrinkToFit();
    REQUIRE(ds.Size() == ds.Capacity());
  }
  SECTION("On non-empty array") {
    DynamicArray<int> ds;
    for (unsigned i = 0; i < 100; ++i)
      ds.PushBack(i);
    ds.ShrinkToFit();
    REQUIRE(ds.Size() == ds.Capacity());
  }
}

TEST_CASE(DS "can reserve capacity", DS) {
  DynamicArray<int> ds;

  SECTION("On empty array with zero capacity") {
    ds.Clear();
    ds.Reserve(100);
    REQUIRE(ds.Capacity() == 100);
  }
  SECTION("On empty array with non-zero capacity") {
    ds.Reserve(100);
    REQUIRE(ds.Capacity() == 100);
  }
  SECTION("On non-empty array") {
    for (unsigned i = 0; i < 10; ++i)
      ds.PushBack(i);
    ds.Reserve(100);
    REQUIRE(ds.Capacity() == 100);
  }
}

TEST_CASE(DS "operator+= should append correctly", DS) {
  SECTION("When both are empty") {
    DynamicArray<int> empty_ds;
    DynamicArray<int> ds;
    ds += empty_ds;
    REQUIRE(ds == empty_ds);
  }
  SECTION("When lhs is empty") {
    DynamicArray<int> lhs;
    DynamicArray<int> rhs;
    const int rhs_elements_count = 10;
    for (int i = 0; i < rhs_elements_count; ++i)
      rhs.PushBack(i);
    lhs += rhs;
    REQUIRE(lhs == rhs);
  }
  SECTION("When rhs is empty") {
    DynamicArray<int> lhs;
    DynamicArray<int> rhs;
    const int lhs_elements_count = 10;
    for (int i = 0; i < lhs_elements_count; ++i)
      lhs.PushBack(i);
    DynamicArray<int> lhs_copy(lhs);
    lhs += rhs;
    REQUIRE(lhs == lhs_copy);
  }
  SECTION("Single element append when" DS " is empty") {
    const int element = 10;
    DynamicArray<int> ds;
    ds += element;
    REQUIRE(ds.Size() == 1);
    REQUIRE(ds.Back() == element);
    REQUIRE(ds.Front() == element);
  }
  SECTION("Single element append when" DS " is empty") {
    const unsigned element = 10;
    DynamicArray<unsigned > ds;
    for (unsigned i = 0; i < element; ++i)
      ds.PushFront(i);
    ds += element;
    REQUIRE(ds.Size() == element + 1);
    REQUIRE(ds.Back() == element);
  }
}