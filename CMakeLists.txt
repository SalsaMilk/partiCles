cmake_minimum_required(VERSION 3.21)
project(partiCles C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCE
        main.c
        SDL/*.c
        )

add_executable(partiCles ${SOURCE} vector.h)

file(GLOB LIBS lib/*.lib)

target_link_libraries(partiCles ${LIBS})
