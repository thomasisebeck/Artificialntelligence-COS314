cmake_minimum_required(VERSION 3.26)
project(Assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(reference)

add_executable(Assignment3
        data.txt
        main.cpp
        Network.cpp
        Network.h
        storage.txt)
