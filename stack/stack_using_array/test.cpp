#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "stack.h"

TEST_CASE("Stack can be created", "[Stack]") {
  SECTION("With default ctor") {
    Stack<int> s;
    REQUIRE(s.Empty() == true);
  }

  SECTION("With capacity param passed to the ctor") {
    Stack<int> s(20);
    REQUIRE(s.Empty() == true);
  }

  SECTION("With copy ctor") {
    Stack<int> s1;
    for (unsigned i = 0; i < 1; ++i)
      s1.Push(i);
    Stack<int> s2(s1);
    REQUIRE(s2.Empty() == s1.Empty());
    REQUIRE(s2.Pop() == s1.Pop());
  }
}

TEST_CASE("Stack push/pop elements", "[Stack]") {
  Stack<int> s;
  for (unsigned i = 0; i < 15; ++i)
    s.Push(i);
  REQUIRE_FALSE(s.Empty());
  REQUIRE(s.Pop() == 14);

  unsigned i = 13;
  while (!s.Empty())
    REQUIRE(s.Pop() == i--);
}

TEST_CASE("Stack operator=", "[Stack]") {
  Stack<int> s1;
  for (unsigned i = 0; i < 10; ++i)
    s1.Push(i);
  Stack<int> s2(20);
  for (unsigned i = 0; i < 20; ++i)
    s1.Push(i);
  s2 = s1;
  REQUIRE(s2.Empty() == s1.Empty());
  REQUIRE(s2.Pop() == s1.Pop());
}