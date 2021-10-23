cmake_minimum_required(VERSION 3.20)
project(SortingStation C)

set(CMAKE_C_STANDARD 99)

include_directories(../Stack ../PostfixCalculator ../AdvancedBracketBalance)

add_executable(SortingStation main.c sortingStationAlgorithm.h
        sortingStationAlgorithm.c ../Stack/stack.c ../Stack/stackTests.c
        ../PostfixCalculator/postfixCalculator.c
        ../PostfixCalculator/postfixCalculatorTests.c)
