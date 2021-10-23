cmake_minimum_required(VERSION 3.20)
project(PostfixCalculator C)

set(CMAKE_C_STANDARD 99)

include_directories(../Stack)

add_executable(PostfixCalculator main.c ../Stack/stackTests.c
        ../Stack/stack.c ../Stack/stackTests.h ../Stack/stack.h postfixCalculator.h postfixCalculatorTests.h postfixCalculator.c postfixCalculatorTests.c)