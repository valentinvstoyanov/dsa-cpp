cmake_minimum_required(VERSION 3.12)
project(deterministic_finite_automaton)

set(CMAKE_CXX_STANDARD 17)

add_executable(deterministic_finite_automaton main.cpp dfa.h)