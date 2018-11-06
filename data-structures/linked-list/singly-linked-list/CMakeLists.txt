cmake_minimum_required(VERSION 3.12)
project(singly-linked-list)

set(CMAKE_CXX_STANDARD 11)

add_executable(singly-linked-list test.cpp singly_linked_list.h lib/catch.hpp)
