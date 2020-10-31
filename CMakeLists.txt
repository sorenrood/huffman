# cmake_minimum_required(VERSION <specify CMake version here>)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffman main.cpp vsarray.cpp vsarray.h tree.cpp tree.h frequencyTable.cpp frequencyTable.h)