cmake_minimum_required(VERSION 3.20)
project(AdvancedBracketBalance C)

set(CMAKE_C_STANDARD 99)

include_directories(../Stack)

add_executable(AdvancedBracketBalance main.c ../Stack/stackTests.c
        ../Stack/stack.c ../Stack/stackTests.h ../Stack/stack.h advancedBracketBalance.h advancedBracketBalance.c advancedBracketBalanceTests.h advancedBracketBalanceTests.c)
