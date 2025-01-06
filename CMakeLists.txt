cmake_minimum_required(VERSION 3.30)
project(tetris_optimized C)

set(CMAKE_C_STANDARD 17)

add_executable(tetris_optimized main.c ../../libraries/console.c tetris.c)
