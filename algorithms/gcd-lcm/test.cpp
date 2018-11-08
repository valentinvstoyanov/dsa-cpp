#define CATCH_CONFIG_MAIN
#include "lib/catch.hpp"
#include "gcd_lcm.h"

TEST_CASE("GCD", "[GCD_LCM]") {
  SECTION("On 2 elements") {
    REQUIRE(GCD(114, 12) == 6);
    REQUIRE(GCD(17, 89) == 1);
    REQUIRE(GCD(1, 1) == 1);
    REQUIRE(GCD(2, 1) == 1);
    REQUIRE(GCD(4, 1) == 1);
    REQUIRE(GCD(2, 4) == 2);
  }
  SECTION("On array") {
    const size_t size = 5;
    const long long arr[size] = {2, 4, 6, 8, 16};
    REQUIRE(GCD(arr, size) == 2);
  }
}

TEST_CASE("LCM", "[GCD_LCM]") {
  SECTION("On 2 elements") {
    REQUIRE(LCM(4, 6) == 12);
    REQUIRE(LCM(2, 3) == 6);
    REQUIRE(LCM(1, 1) == 1);
    REQUIRE(LCM(2, 2) == 2);
  }
  SECTION("On array") {
    const size_t size = 5;
    const long long arr[size] = {2, 7, 3, 9, 4}; ;
    REQUIRE(GCD(arr, size) == 252);
  }
}