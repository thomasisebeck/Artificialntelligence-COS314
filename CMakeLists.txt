cmake_minimum_required(VERSION 3.24)
project(COS314New)

set(CMAKE_CXX_STANDARD 14)

include_directories(Assignment3)

add_executable(COS314New
        Assignment3/main.cpp
        Assignment3/Network.cpp
        Assignment3/Network.h)
