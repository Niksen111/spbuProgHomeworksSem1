cmake_minimum_required(VERSION 3.20)
project(SortingStationAlgorithm C)

set(CMAKE_C_STANDARD 99)

include_directories(../Stack ../AdvancedBracketBalance)

add_executable(SortingStationAlgorithm main.c sortingStationAlgorithm.h
        sortingStationAlgorithm.c ../Stack/stackTests.c
        ../Stack/stack.c ../Stack/stackTests.h ../Stack/stack.h
        ../AdvancedBracketBalance/advancedBracketBalance.c
        ../AdvancedBracketBalance/advancedBracketBalance.h)
