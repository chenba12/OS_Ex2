cmake_minimum_required(VERSION 3.25)
project(OS_Ex2 C)

set(CMAKE_C_STANDARD 99)

add_executable(OS_Ex2 cmp.c copy.c codecA.c codecB.c encode.c stshell.c decode.c)
