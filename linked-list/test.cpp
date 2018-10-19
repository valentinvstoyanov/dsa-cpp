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