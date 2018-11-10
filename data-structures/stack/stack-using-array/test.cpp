#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "stack.h"
#define DS " Stack "

TEST_CASE(DS "can be created with default ctor", DS) {
  REQUIRE_NOTHROW(Stack<int>());
}

TEST_CASE(DS "can be created with initial capacity", DS) {
  const size_t initial_capacity = 100;
  REQUIRE_NOTHROW(Stack<int>(initial_capacity));
}

TEST_CASE("Empty() returns true on empty" DS, DS) {
  REQUIRE(Stack<char>().Empty());
}

TEST_CASE("Size() returns zero on empty" DS, DS) {
  REQUIRE(Stack<char>().Size() == 0);
}

TEST_CASE("Clear() should not throw when called on empty" DS, DS) {
  REQUIRE_NOTHROW(Stack<char>().Clear());
}

TEST_CASE("Push elements to" DS "should not throw", DS) {
  Stack<unsigned> ds;
  const unsigned start = 1;
  const unsigned end = 129;
  for (unsigned i = start; i <= end; ++i)
    REQUIRE_NOTHROW(ds.Push(i));
  REQUIRE(ds.Size() == end - start + 1);
  REQUIRE_FALSE(ds.Empty());
}

TEST_CASE("Pop elements from" DS "should not throw", DS) {
  const int test_arr_size = 5;
  const int test_arr[test_arr_size] = {5, 1, 2, 4, 3};
  Stack<int> ds;
  for (int i = 0; i < test_arr_size; ++i)
    ds.Push(test_arr[i]);
  for (int i = 0; i < test_arr_size; ++i)
    REQUIRE(ds.Pop() == test_arr[test_arr_size - i - 1]);
  REQUIRE(ds.Empty());
  REQUIRE(ds.Size() == 0);
}

TEST_CASE("Clear() non-empty" DS, DS) {
  Stack<int> ds;
  const unsigned e1 = 0, e2 = 1, e3 = 2;
  ds.Push(e1); ds.Push(e2); ds.Push(e3);

  SECTION("Once") {
    ds.Clear();
    REQUIRE(ds.Empty());
    REQUIRE(ds.Size() == 0);
  }
  SECTION("More times") {
    for (int i = 0; i < 10; ++i) {
      REQUIRE_NOTHROW(ds.Clear());
      REQUIRE(ds.Empty());
      REQUIRE(ds.Size() == 0);
    }
  }
}

TEST_CASE(DS "comparison", DS) {
  Stack<int> ds1(10);
  Stack<int> ds2(10);

  SECTION("On empty" DS "should be true") {
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with same elements should be true") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.Push(i);
      ds2.Push(i);
    }
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with different elements should be false") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.Push(i);
      ds2.Push(i + 10);
    }
    REQUIRE_FALSE(ds1 == ds2);
    REQUIRE(ds1 != ds2);
  }
}

TEST_CASE(DS "can be created with copy ctor", DS) {
  SECTION("From empty" DS) {
    Stack<int> empty_ds;
    Stack<int> ds(empty_ds);
    REQUIRE(ds == empty_ds);
  }
  SECTION("From non-empty" DS) {
    Stack<int> ds;
    const unsigned e1 = 0, e2 = 1, e3 = 2;
    ds.Push(e1); ds.Push(e2); ds.Push(e3);

    Stack<int> copy_of_ds(ds);
    REQUIRE(copy_of_ds == ds);
  }
}

TEST_CASE(DS "operator=", DS) {
  SECTION("On empty" DS) {
    Stack<int> ds1;
    Stack<int> ds2(0);
    ds2 = ds1;
    REQUIRE(ds2 == ds1);
  }
  SECTION("On non-empty" DS) {
    Stack<int> da1;
    Stack<int> da2(0);
    da1.Push(10);
    da2.Push(110);
    da2 = da1;
    REQUIRE(da2 == da1);
  }
}

TEST_CASE(DS "operator+= should append correctly", DS) {
  SECTION("When both are empty") {
    Stack<int> empty_ds;
    Stack<int> ds;
    ds += empty_ds;
    REQUIRE(ds == empty_ds);
  }
  SECTION("When lhs is empty") {
    Stack<int> lhs;
    Stack<int> rhs;
    const int rhs_elements_count = 10;
    for (int i = 0; i < rhs_elements_count; ++i)
      rhs.Push(i);
    lhs += rhs;
    REQUIRE(lhs == rhs);
  }
  SECTION("When rhs is empty") {
    Stack<int> lhs;
    Stack<int> rhs;
    const int lhs_elements_count = 10;
    for (int i = 0; i < lhs_elements_count; ++i)
      lhs.Push(i);
    Stack<int> lhs_copy(lhs);
    lhs += rhs;
    REQUIRE(lhs == lhs_copy);
  }
  SECTION("Single element append when" DS " is empty") {
    const int element = 10;
    Stack<int> ds;
    ds += element;
    REQUIRE(ds.Size() == 1);
    REQUIRE(ds.Pop() == element);
  }
  SECTION("Single element append when" DS " is empty") {
    const unsigned element = 10;
    Stack<unsigned > ds;
    for (unsigned i = 0; i < element; ++i)
      ds.Push(i);
    ds += element;
    REQUIRE(ds.Size() == element + 1);
    REQUIRE(ds.Pop() == element);
  }
}