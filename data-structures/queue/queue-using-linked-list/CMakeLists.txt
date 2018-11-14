cmake_minimum_required(VERSION 3.12)
project(queue_using_linked_list)

set(CMAKE_CXX_STANDARD 14)

add_executable(queue_using_linked_list test.cc queue.h lib/catch.hpp)