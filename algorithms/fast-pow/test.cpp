#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "fast_pow.h"

TEST_CASE("Fast power with positive integers", "[FastPow]") {
  REQUIRE(FastPow(10, 2) == 100);
  REQUIRE(FastPow(2, 10) == 1024);
  REQUIRE(FastPow(5, 4) == 625);
}

TEST_CASE("Fast power with 0 power", "[FastPow]") {
  REQUIRE(FastPow(10, 0) == 1);
  REQUIRE(FastPow(2, 0) == 1);
  REQUIRE(FastPow(-5, 0) == 1);
  REQUIRE(FastPow(50000000, 0) == 1);
}

TEST_CASE("Fast power with negative base", "[FastPow]") {
  REQUIRE(FastPow(-10, 2) == 100);
  REQUIRE(FastPow(-10, 3) == -1000);
}