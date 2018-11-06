cmake_minimum_required(VERSION 3.12)
project(queue_using_array)

set(CMAKE_CXX_STANDARD 14)

add_executable(queue_using_array test.cpp lib/catch.hpp queue.h)