cmake_minimum_required(VERSION 3.20)
project(AVLTree C)

set(CMAKE_C_STANDARD 99)

add_executable(AVLTree main.c avlTree.c avlTreeTests.c)
