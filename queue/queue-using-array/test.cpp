#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "queue.h"

TEST_CASE("Queue can be created", "[Queue]") {
  SECTION("With default ctor") {
    Queue<int> q;
    REQUIRE(q.Empty() == true);
  }

  SECTION("With capacity param passed to the ctor") {
    Queue<int> q(20);
    REQUIRE(q.Empty() == true);
  }

  SECTION("With copy ctor") {
    Queue<int> q1;
    for (unsigned i = 0; i < 1; ++i)
      q1.Enqueue(i);
    Queue<int> q2(q1);
    REQUIRE(q2.Empty() == q1.Empty());
    REQUIRE(q1.Dequeue() == q2.Dequeue());
  }
}

TEST_CASE("Queue enqueue/dequeue elements", "[Queue]") {
  Queue<int> q;
  for (unsigned i = 0; i < 3; ++i)
    q.Enqueue(i);
  REQUIRE_FALSE(q.Empty());

  unsigned i = 0;
  while (!q.Empty())
    REQUIRE(q.Dequeue() == i++);
}

TEST_CASE("Queue operator=", "[Queue]") {
  Queue<int> q1;
  for (unsigned i = 0; i < 10; ++i)
    q1.Enqueue(i);
  Queue<int> q2(20);
  for (unsigned i = 0; i < 20; ++i)
    q1.Enqueue(i);
  q2 = q1;
  REQUIRE(q2.Empty() == q1.Empty());
  REQUIRE(q2.Dequeue() == q1.Dequeue());
}

TEST_CASE("Queue += value", "[Queue]") {
  Queue<int> q;
  for (unsigned i = 0; i < 15; ++i)
    q += i;
  REQUIRE_FALSE(q.Empty());
  REQUIRE(q.Dequeue() == 0);
}