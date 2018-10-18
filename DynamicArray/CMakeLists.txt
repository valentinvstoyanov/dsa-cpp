cmake_minimum_required(VERSION 3.12)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 11)

add_executable(DynamicArray test.cpp DynamicArray.h lib/catch.hpp)