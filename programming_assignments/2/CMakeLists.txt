cmake_minimum_required(VERSION 2.8)
project(DCT)

set(CMAKE_C_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES_DCT myDCT.cpp macroblockManager.h macroblockManager.cpp pgmFileParser.h pgmFileParser.cpp pgmFileParser.h macroblockManager.cpp block.cpp block.h macroblock.cpp macroblock.h dct.h dct.cpp)
set(SOURCE_FILES_IDCT myIDCT.cpp macroblockManager.h macroblockManager.cpp pgmFileParser.h pgmFileParser.cpp pgmFileParser.h macroblockManager.cpp block.cpp block.h macroblock.cpp macroblock.h dct.h dct.cpp)
add_executable(myDCT ${SOURCE_FILES_DCT})
add_executable(myIDCT ${SOURCE_FILES_IDCT})
