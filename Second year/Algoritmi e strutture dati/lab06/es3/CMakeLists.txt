cmake_minimum_required(VERSION 3.27)
project(es3 C)

set(CMAKE_C_STANDARD 99)

add_executable(es3 main.c
        personaggio.h
        inventario.h
        statistiche.h
        inventario.c
        personaggio.c
        statistiche.c)
