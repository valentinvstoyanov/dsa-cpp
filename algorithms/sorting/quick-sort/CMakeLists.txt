cmake_minimum_required(VERSION 3.13)
project(quick_sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(quick_sort quick_sort.h lib/catch.hpp test.cc)