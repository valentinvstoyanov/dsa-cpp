cmake_minimum_required(VERSION 3.12)
project(stack_using_array)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_using_array test.cpp stack.h lib/catch.hpp)