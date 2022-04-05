cmake_minimum_required(VERSION 3.20)
project(List C)

set(CMAKE_C_STANDARD 99)

add_executable(List main.c sortedList.c sortedListTests.c)
