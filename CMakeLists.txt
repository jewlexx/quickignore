cmake_minimum_required(VERSION 3.25)
project(cignore C)

set(CMAKE_C_STANDARD 11)

add_executable(cignore main.c slicing.c include/slicing.h)
