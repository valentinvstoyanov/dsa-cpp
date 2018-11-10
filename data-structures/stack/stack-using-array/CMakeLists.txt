cmake_minimum_required(VERSION 3.12)
project(stack-using-array)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack-using-array test.cc stack.h lib/catch.hpp)
