cmake_minimum_required(VERSION 3.5)
project(mpihello C)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_MAKE_PROGRAM "/usr/bin/make")
set(CMAKE_C_STANDARD 11)

include_directories("/usr/include/mpich/")

link_libraries(mpich)
add_executable(mpihello main.c)
target_link_libraries(mpihello mpich)

