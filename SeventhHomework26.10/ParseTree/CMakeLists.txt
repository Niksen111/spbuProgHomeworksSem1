cmake_minimum_required(VERSION 3.20)
project(ParseTree C)

set(CMAKE_C_STANDARD 99)

add_executable(ParseTree main.c parseTree.c parseTree.h parseTreeTests.c parseTreeTests.h)
