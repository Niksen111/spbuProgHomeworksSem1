cmake_minimum_required(VERSION 3.20)
project(MergeSort C)

set(CMAKE_C_STANDARD 99)

add_executable(MergeSort main.c mergeSorting.c
        list.c mergeSortingTests.c listTests.c supportFunctions.c supportFunctions.h)
