cmake_minimum_required(VERSION 3.12)
project(linked-list)

set(CMAKE_CXX_STANDARD 11)

add_executable(linked-list test.cpp linked_list.h lib/catch.hpp)
