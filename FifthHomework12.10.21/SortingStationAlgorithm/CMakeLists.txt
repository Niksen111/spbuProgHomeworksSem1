cmake_minimum_required(VERSION 3.20)
project(SortingStationAlgorithm C)

set(CMAKE_C_STANDARD 99)

include_directories(../Stack ../AdvancedBracketBalance
        ../PostfixCalculator)

add_executable(SortingStationAlgorithm main.c
        sortingStationAlgorithm.c ../Stack/stackTests.c
        ../Stack/stack.c
        ../AdvancedBracketBalance/advancedBracketBalance.c
        ../PostfixCalculator/postfixCalculator.c
        sortingStationAlgorithmTests.c
        ../AdvancedBracketBalance/advancedBracketBalanceTests.c
        ../PostfixCalculator/postfixCalculatorTests.c)
