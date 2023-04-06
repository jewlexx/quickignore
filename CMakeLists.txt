cmake_minimum_required(VERSION 3.25)
project(cignore C)

set(CMAKE_C_STANDARD 11)

add_executable(cignore src/main.c src/slicing.c include/slicing.h src/args.c include/args.h)
