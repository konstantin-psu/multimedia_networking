cmake_minimum_required(VERSION 2.8)
project(jpeg_dct)

set(CMAKE_C_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES myDCT.cpp macroblockManager.h pgmEncoded.h pgmEncoded.cpp pgmEncoded.h macroblockManager.cpp block.cpp block.h macroblock.cpp macroblock.h)
add_executable(myDCT ${SOURCE_FILES} macroblockManager.cpp)