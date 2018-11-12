cmake_minimum_required(VERSION 3.12)
project(dynamic-array)

set(CMAKE_CXX_STANDARD 11)

add_executable(dynamic-array test.cc dynamic_array.h lib/catch.hpp)
