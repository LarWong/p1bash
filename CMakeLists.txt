cmake_minimum_required(VERSION 3.12)
project(p1bash C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(p1bash
        main.c
        shell.c
        shell.h)
