# cmake_minimum_required(VERSION <specify CMake version here>)
project(TP2_C__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TP2_C__ ${SOURCE_FILES})