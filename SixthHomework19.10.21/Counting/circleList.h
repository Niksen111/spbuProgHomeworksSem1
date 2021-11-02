#pragma once
#include <stdbool.h>

// type of data that will be stored in the CircleList
typedef int Value;

// CircleList structure
typedef struct CircleList
{
    Value value;
    struct CircleList* next;
} CircleList;

// created an empty CircleList
CircleList* createCircleList();

// checks if the CircleList is empty
bool circleListIsEmpty(CircleList** currentPosition);

// adds an element after the current to the CircleList
int push(CircleList** currentPosition, Value value);

// Moves the pointer to the next element
void switchToNext(CircleList** currentPosition);

// removes the current element and moves the pointer to the next
int popCurrent(CircleList** currentPosition, int* errorCode);

// removes the entire CircleList
void deleteCircleList(CircleList** currentPosition);

// prints the entire CircleList
void printCircleList(CircleList** currentPosition);