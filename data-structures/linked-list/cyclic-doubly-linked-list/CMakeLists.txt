cmake_minimum_required(VERSION 3.12)
project(cyclic_doubly_linked_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(cyclic_doubly_linked_list test.cc doubly_linked_list.h lib/catch.hpp)