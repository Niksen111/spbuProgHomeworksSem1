cmake_minimum_required(VERSION 3.20)
project(Stack C)

set(CMAKE_C_STANDARD 99)

add_executable(Stack main.c stack.h stack.c stackTests.c stackTests.h)
