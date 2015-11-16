cmake_minimum_required(VERSION 2.8)
project(DCT)

set(CMAKE_C_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES_DCT myDCT.cpp macroblockManager.h macroblockManager.cpp macroblockManager.cpp block.cpp block.h macroblock.cpp macroblock.h rawInput.h rawInput.cpp)
set(SOURCE_FILES_IDCT myIDCT.cpp macroblockManager.h macroblockManager.cpp macroblockManager.cpp block.cpp block.h macroblock.cpp macroblock.h rawInput.h rawInput.cpp)
add_executable(myDCT ${SOURCE_FILES_DCT})
add_executable(myIDCT ${SOURCE_FILES_IDCT})
