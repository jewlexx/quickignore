cmake_minimum_required(VERSION 3.25)
project(quickignore C)

set(CMAKE_C_STANDARD 11)

add_executable(quickignore src/main.c src/slicing.c include/slicing.h src/args.c include/args.h src/requests.c include/requests.h)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(quickignore PRIVATE CURL::libcurl)
