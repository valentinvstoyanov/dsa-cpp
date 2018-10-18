cmake_minimum_required(VERSION 3.12)
project(LinkedList)

set(CMAKE_CXX_STANDARD 11)

add_executable(LinkedList test.cpp LinkedList.h lib/catch.hpp)