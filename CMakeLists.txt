cmake_minimum_required(VERSION 3.21)
project(partiCles C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2 -lSDL2_gfx")

add_executable(partiCles main.c vector.h)

target_link_libraries(partiCles m)
