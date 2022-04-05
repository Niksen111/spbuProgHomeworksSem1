cmake_minimum_required(VERSION 3.20)
project(ModulesAndFiles C)

set(CMAKE_C_STANDARD 99)

add_executable(ModulesAndFiles myQSort.c ModulesAndFiles.c
        testMyQSort.c WorkWithArrays.c)