#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "queue.h"
#define DS " Queue "

TEST_CASE(DS "can be created with default ctor", DS) {
  REQUIRE_NOTHROW(Queue<int>());
}

TEST_CASE("Empty() returns true on empty" DS, DS) {
  REQUIRE(Queue<char>().Empty());
}

TEST_CASE("Size() returns zero on empty" DS, DS) {
  REQUIRE(Queue<char>().Size() == 0);
}

TEST_CASE("Clear() should not throw when called on empty" DS, DS) {
  REQUIRE_NOTHROW(Queue<char>().Clear());
}

TEST_CASE("Enqueue() elements to" DS "should not throw", DS) {
  Queue<unsigned> ds;
  const unsigned start = 1;
  const unsigned end = 129;
  for (unsigned i = start; i <= end; ++i)
    REQUIRE_NOTHROW(ds.Enqueue(i));
  REQUIRE(ds.Size() == end - start + 1);
  REQUIRE_FALSE(ds.Empty());
}

TEST_CASE("Dequeue() elements from" DS "should not throw", DS) {
  const int test_arr_size = 5;
  const int test_arr[test_arr_size] = {5, 1, 2, 4, 3};
  Queue<int> ds;
  for (int i = 0; i < test_arr_size; ++i)
    ds.Enqueue(test_arr[i]);
  for (int i = 0; i < test_arr_size; ++i)
    REQUIRE(ds.Dequeue() == test_arr[i]);
  REQUIRE(ds.Empty());
  REQUIRE(ds.Size() == 0);
}

TEST_CASE("Clear() non-empty" DS, DS) {
  Queue<int> ds;
  const unsigned e1 = 0, e2 = 1, e3 = 2;
  ds.Enqueue(e1); ds.Enqueue(e2); ds.Enqueue(e3);

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
  Queue<int> ds1;
  Queue<int> ds2;

  SECTION("On empty" DS "should be true") {
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with same elements should be true") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.Enqueue(i);
      ds2.Enqueue(i);
    }
    REQUIRE(ds1 == ds2);
    REQUIRE_FALSE(ds1 != ds2);
  }
  SECTION("On non-empty" DS "with different elements should be false") {
    for (unsigned i = 0; i < 10; ++i) {
      ds1.Enqueue(i);
      ds2.Enqueue(i + 10);
    }
    REQUIRE_FALSE(ds1 == ds2);
    REQUIRE(ds1 != ds2);
  }
}

TEST_CASE(DS "can be created with copy ctor", DS) {
  SECTION("From empty" DS) {
    Queue<int> empty_ds;
    Queue<int> ds(empty_ds);
    REQUIRE(ds == empty_ds);
  }
  SECTION("From non-empty" DS) {
    Queue<int> ds;
    const unsigned e1 = 0, e2 = 1, e3 = 2;
    ds.Enqueue(e1); ds.Enqueue(e2); ds.Enqueue(e3);

    Queue<int> copy_of_ds(ds);
    REQUIRE(copy_of_ds == ds);
  }
}

TEST_CASE(DS "operator=", DS) {
  SECTION("On empty" DS) {
    Queue<int> ds1;
    Queue<int> ds2;
    ds2 = ds1;
    REQUIRE(ds2 == ds1);
  }
  SECTION("On non-empty" DS) {
    Queue<int> ds1;
    Queue<int> ds2;
    ds1.Enqueue(10);
    ds2.Enqueue(110);
    ds2 = ds1;
    REQUIRE(ds2 == ds1);
  }
}

TEST_CASE(DS "operator+= should append correctly", DS) {
  SECTION("When both are empty") {
    Queue<int> empty_ds;
    Queue<int> ds;
    ds += empty_ds;
    REQUIRE(ds == empty_ds);
  }
  SECTION("When lhs is empty") {
    Queue<int> lhs;
    Queue<int> rhs;
    const int rhs_elements_count = 10;
    for (int i = 0; i < rhs_elements_count; ++i)
      rhs.Enqueue(i);
    lhs += rhs;
    REQUIRE(lhs == rhs);
  }
  SECTION("When rhs is empty") {
    Queue<int> lhs;
    Queue<int> rhs;
    const int lhs_elements_count = 10;
    for (int i = 0; i < lhs_elements_count; ++i)
      lhs.Enqueue(i);
    Queue<int> lhs_copy(lhs);
    lhs += rhs;
    REQUIRE(lhs == lhs_copy);
  }
  SECTION("Single element append when" DS " is empty") {
    const int element = 10;
    Queue<int> ds;
    ds += element;
    REQUIRE(ds.Size() == 1);
    REQUIRE(ds.Dequeue() == element);
  }
  SECTION("Single element append when" DS " is empty") {
    const unsigned element = 10;
    Queue<unsigned > ds;
    for (unsigned i = 0; i < element; ++i)
      ds.Enqueue(i);
    ds += element;
    REQUIRE(ds.Size() == element + 1);
    for (unsigned i = 0; i < element; ++i)
      REQUIRE(ds.Dequeue() == i);
    REQUIRE(ds.Dequeue() == element);
  }
}