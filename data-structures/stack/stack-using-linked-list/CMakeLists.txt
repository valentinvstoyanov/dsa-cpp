cmake_minimum_required(VERSION 3.12)
project(stack_using_linked_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_using_linked_list test.cc stack.h lib/catch.hpp)