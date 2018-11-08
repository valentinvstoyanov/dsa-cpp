cmake_minimum_required(VERSION 3.12)
project(gcd-lcm)

set(CMAKE_CXX_STANDARD 14)

add_executable(gcd-lcm test.cpp lib/catch.hpp gcd_lcm.h gcd_lcm.cc)