cmake_minimum_required(VERSION 3.6)
project(TP_CPP_2)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I")

file(GLOB SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
        )

add_executable(TP_CPP_2 ${SOURCE_FILES})