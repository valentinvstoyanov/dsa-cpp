#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "fast_pow.h"

TEST_CASE("Fast power with positive integers", "[fast_pow]") {
  REQUIRE(fast_pow(10, 2) == 100);
  REQUIRE(fast_pow(2, 10) == 1024);
  REQUIRE(fast_pow(5, 4) == 625);
}

TEST_CASE("Fast power with 0 power", "[fast_pow]") {
  REQUIRE(fast_pow(10, 0) == 1);
  REQUIRE(fast_pow(2, 0) == 1);
  REQUIRE(fast_pow(-5, 0) == 1);
  REQUIRE(fast_pow(50000000, 0) == 1);
}

TEST_CASE("Fast power with negative base", "[fast_pow]") {
  REQUIRE(fast_pow(-10, 2) == 100);
}