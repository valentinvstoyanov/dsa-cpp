cmake_minimum_required(VERSION 3.15)
project(thread_safe_queue)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(thread_safe_queue main.cpp thread_safe_queue.h)