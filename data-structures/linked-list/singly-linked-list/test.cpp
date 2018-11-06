#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "singly_linked_list.h"

TEST_CASE("SinglyLinkedList can be created", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  REQUIRE(list.Empty());
  REQUIRE(list.Size() == 0);
}

TEST_CASE("SinglyLinkedList push front elements", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  REQUIRE_FALSE(list.Empty());
  REQUIRE(list.Size() == 2);
}

TEST_CASE("SinglyLinkedList pop front elements", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  list.PopFront();
  list.PopFront();
  REQUIRE(list.Empty());
}

TEST_CASE("SinglyLinkedList push back elements", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  list.PushBack(10);
  list.PushBack(100);
  REQUIRE_FALSE(list.Empty());
  REQUIRE(list.Size() == 2);
  REQUIRE(list.Back() == 100);
}

TEST_CASE("SinglyLinkedList pop back elements", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;

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

TEST_CASE("SinglyLinkedList get front/back element", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  list.PushFront(10);
  list.PushFront(100);
  REQUIRE(list.Back() == 10);
  REQUIRE(list.Front() == 100);
}

TEST_CASE("SinglyLinkedList copy ctor", "[SinglyLinkedList]") {
  SinglyLinkedList<int> l1;
  l1.PushFront(20);
  l1.PushFront(10);
  SinglyLinkedList<int> l2(l1);
  REQUIRE(l2.Front() == l1.Front());
  REQUIRE(l2.Size() == l1.Size());
  REQUIRE(l2.Back() == l1.Back());
}

TEST_CASE("SinglyLinkedList operator=", "[SinglyLinkedList]") {
  SinglyLinkedList<int> l1;
  l1.PushFront(20);
  l1.PushFront(10);
  SinglyLinkedList<int> l2;
  l2.PushFront(123);
  l2 = l1;
  REQUIRE(l2.Front() == l1.Front());
  REQUIRE(l2.Size() == l1.Size());
  REQUIRE(l2.Back() == l1.Back());
}

TEST_CASE("SinglyLinkedList append element", "[SinglyLinkedList]") {
  SinglyLinkedList<int> list;
  list.PushFront(20);
  list += 2;
  REQUIRE(list.Size() == 2);
  REQUIRE(list.Back() == 2);
}

TEST_CASE("SinglyLinkedList append other SinglyLinkedList", "[SinglyLinkedList]") {
  SinglyLinkedList<int> l1;
  l1.PushFront(20);
  SinglyLinkedList<int> l2;
  for (int i = 0; i < 10; ++i)
    l2 += i;
  l1 += l2;
  REQUIRE(l1.Size() == l2.Size() + 1);
  REQUIRE(l1.Back() == l2.Back());
}

TEST_CASE("SinglyLinkedList comparison", "[SinglyLinkedList]") {
  SinglyLinkedList<int> l1;
  SinglyLinkedList<int> l2;
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