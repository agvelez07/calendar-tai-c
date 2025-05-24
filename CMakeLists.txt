cmake_minimum_required(VERSION 3.20)
project(agenda C)

set(CMAKE_C_STANDARD 11)

add_executable(agenda
        main.c
        agenda.c
        sala.c
        evento.c
        data.c
)
