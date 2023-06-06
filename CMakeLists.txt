cmake_minimum_required(VERSION 3.24)
project(COS314New)

set(CMAKE_CXX_STANDARD 14)

include_directories(Assigment3Retry)

add_executable(COS314New
        Assigment3Retry/Matrix.cpp
        Assigment3Retry/Matrix.h Assigment3Retry/Network.cpp Assigment3Retry/sharedTypes.h Assigment3Retry/main.cpp)
