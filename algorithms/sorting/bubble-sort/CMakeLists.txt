cmake_minimum_required(VERSION 3.12)
project(bubble_sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(bubble_sort test.cc bubble_sort.h lib/catch.hpp)
