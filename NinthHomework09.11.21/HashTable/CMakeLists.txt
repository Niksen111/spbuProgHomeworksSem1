cmake_minimum_required(VERSION 3.20)
project(HashTable C)

set(CMAKE_C_STANDARD 99)

add_executable(HashTable main.c hashTable.c hashTable.h list.c list.h listTests.c listTests.h)
