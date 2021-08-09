cmake_minimum_required(VERSION 3.17)
project(HTM)

set(CMAKE_CXX_STANDARD 20)

add_executable(HTM
        main.cpp
        src/Region.h
        src/Region.cpp
        src/Cell.h
        src/Cell.cpp
        src/Segment.h
        src/Segment.cpp)