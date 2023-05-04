cmake_minimum_required(VERSION 3.24)
project(COS314)

set(CMAKE_CXX_STANDARD 14)

include_directories(Assignment1)

add_executable(COS314
        Assignment2/main.cpp
        Assignment2/sharedTypes.h)
