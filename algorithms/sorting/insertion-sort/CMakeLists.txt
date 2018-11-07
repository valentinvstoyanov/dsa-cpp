cmake_minimum_required(VERSION 3.12)
project(insertion_sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(insertion_sort test.cpp lib/catch.hpp insertion_sort.h)