cmake_minimum_required(VERSION 3.12)
project(fast-pow)

set(CMAKE_CXX_STANDARD 14)

add_executable(fast-pow test.cpp fast_pow.h lib/catch.hpp)