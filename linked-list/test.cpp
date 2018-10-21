#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "linked_list.h"

TEST_CASE("LinkedList can be created", "[LinkedList]") {
  LinkedList<int> list;
  REQUIRE(list.Empty());
  REQUIRE(list.Size() == 0);
}

TEST_CASE("LinkedList push front elements", "[LinkedList]") {
  LinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  REQUIRE_FALSE(list.Empty());
  REQUIRE(list.Size() == 2);
}

TEST_CASE("LinkedList pop front elements", "[LinkedList]") {
  LinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  list.PopFront();
  list.PopFront();
  REQUIRE(list.Empty());
}

TEST_CASE("LinkedList push back elements", "[LinkedList]") {
  LinkedList<int> list;
  list.PushBack(10);
  list.PushBack(100);
  REQUIRE_FALSE(list.Empty());
  REQUIRE(list.Size() == 2);
  REQUIRE(list.Back() == 100);
}

TEST_CASE("LinkedList pop back elements", "[LinkedList]") {
  LinkedList<int> list;

  SECTION("With 1 element") {
    list.PushBack(10);
    list.PopBack();
    REQUIRE(list.Empty());
  }

  SECTION("With >1 elements") {
    list.PushBack(10);
    list.PushBack(100);
    list.PopBack();
    list.PopBack();
    REQUIRE(list.Empty());
  }
}

TEST_CASE("LinkedList get front/back element", "[LinkedList]") {
  LinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  REQUIRE(list.Back() == 10);
  REQUIRE(list.Front() == 100);
}

TEST_CASE("LinkedList copy ctor", "[LinkedList]") {
  LinkedList<int> l1;
  l1.PushFront(20);
  l1.PushFront(10);
  LinkedList<int> l2(l1);
  REQUIRE(l2.Front() == l1.Front());
  REQUIRE(l2.Size() == l1.Size());
  REQUIRE(l2.Back() == l1.Back());
}

TEST_CASE("LinkedList operator=", "[LinkedList]") {
  LinkedList<int> l1;
  l1.PushFront(20);
  l1.PushFront(10);
  LinkedList<int> l2;
  l2.PushFront(123);
  l2 = l1;
  REQUIRE(l2.Front() == l1.Front());
  REQUIRE(l2.Size() == l1.Size());
  REQUIRE(l2.Back() == l1.Back());
}

TEST_CASE("LinkedList append element", "[LinkedList]") {
  LinkedList<int> list;
  list.PushFront(20);
  list += 2;
  REQUIRE(list.Size() == 2);
  REQUIRE(list.Back() == 2);
}

TEST_CASE("LinkedList append other LinkedList", "[LinkedList]") {
  LinkedList<int> l1;
  l1.PushFront(20);
  LinkedList<int> l2;
  for (int i = 0; i < 10; ++i)
    l2 += i;
  l1 += l2;
  REQUIRE(l1.Size() == l2.Size() + 1);
  REQUIRE(l1.Back() == l2.Back());
}

TEST_CASE("LinkedList comparison", "[LinkedList]") {
  LinkedList<int> l1;
  LinkedList<int> l2;
  for (unsigned i = 0; i < 10; ++i) {
    l1.PushFront(i);
    l2.PushFront(i);
  }

  REQUIRE(l1 == l2);
  REQUIRE_FALSE(l1 != l2);

  l1.PopBack();
  REQUIRE_FALSE(l1 == l2);
  REQUIRE(l1 != l2);
}