cmake_minimum_required(VERSION 3.25)
project(cignore C)

set(CMAKE_C_STANDARD 11)

set(msys_INCLUDE_DIR "F:/scoop/apps/msys2/current/usr/include")
include_directories(${msys_INCLUDE_DIR})

add_executable(cignore src/main.c src/slicing.c include/slicing.h src/args.c include/args.h src/requests.c include/requests.h)

target_link_libraries(cignore "F:/scoop/apps/msys2/current/usr/lib/libcurl.dll.a")
target_link_libraries(cignore "F:/scoop/apps/msys2/current/usr/lib/libssl.dll.a")
