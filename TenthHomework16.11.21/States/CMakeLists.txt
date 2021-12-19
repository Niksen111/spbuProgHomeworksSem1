cmake_minimum_required(VERSION 3.21)
project(States C)

set(CMAKE_C_STANDARD 99)

add_executable(States main.c sortedList.c sortedListTests.c states.c statesTests.c statesTests.h)
