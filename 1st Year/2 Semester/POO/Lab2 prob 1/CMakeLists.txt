cmake_minimum_required(VERSION 3.26)
project(DemonTime C)

set(CMAKE_C_STANDARD 11)

add_executable(DemonTime main.c
        participant.h
        participant.c
        myList.h
        validator.h
        validator.c
        myList.c
        service.h
        service.c

)


