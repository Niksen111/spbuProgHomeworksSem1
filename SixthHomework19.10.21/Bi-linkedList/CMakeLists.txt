cmake_minimum_required(VERSION 3.20)
project(Bi_linkedList C)

set(CMAKE_C_STANDARD 99)

add_executable(Bi_linkedList main.c bi-linkedList.h
        bi-linkedList.c)
