cmake_minimum_required(VERSION 3.17)
project(indice_analitico C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(indice_analitico
        header.h
        main.c)
