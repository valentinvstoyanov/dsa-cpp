cmake_minimum_required(VERSION 3.12)
project(selection_sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(selection_sort test.cc selection_sort.h lib/catch.hpp)