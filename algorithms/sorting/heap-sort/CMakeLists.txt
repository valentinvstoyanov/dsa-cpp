cmake_minimum_required(VERSION 3.13)
project(heap_sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(heap_sort heap_sort.h test.cc lib/catch.hpp)