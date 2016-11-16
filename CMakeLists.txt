# cmake_minimum_required(VERSION <specify CMake version here>)
project(TP2_C__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# USE MAKEFILE
add_custom_target(TP2_C__ COMMAND make -C ${TP2_C___SOURCE_DIR})