cmake_minimum_required(VERSION 2.8)
project(jpeg_dct)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES myDCT.c)
add_executable(jpeg_dct ${SOURCE_FILES})