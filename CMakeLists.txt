cmake_minimum_required(VERSION 3.30)
project(saod2)

set(CMAKE_CXX_STANDARD 20)

add_executable(saod2 main.cpp
        iofunctions.cpp
        iofunctions.h
        MergeSort.cpp
        MergeSort.h)

add_executable(saod2Hash mainhash.cpp)
add_executable(saod2hash2 mainhash2.cpp)
add_executable(digitalsort DigitalSort.cpp)
