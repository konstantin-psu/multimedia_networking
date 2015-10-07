cmake_minimum_required(VERSION 2.8)
project(Guesser)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES huffman.c)
add_executable(app_exe ${SOURCE_FILES})
