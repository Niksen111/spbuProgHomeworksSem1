#pragma once
#include <stdbool.h>

// type of data that will be stored in the CircleList
typedef int Value;

// CircleList structure
typedef struct CircleList CircleList;

// created an empty CircleList
CircleList* createCircleList();

// checks if the CircleList is empty
bool circleListIsEmpty(CircleList** currentPosition);

// adds an element after the current to the CircleList
int push(CircleList** currentPosition, Value value);

// Moves the pointer to the next element
void switchToNext(CircleList** currentPosition);

// moves the pointer to n elements
void switchToN(CircleList** currentPosition, int n);

// removes the current element and moves the pointer to the next
int popNext(CircleList** currentPosition, int* errorCode);

// removes the entire CircleList
void deleteCircleList(CircleList** currentPosition);

// gets value from current position of CircleList
Value getCurrentPositionValue(CircleList* currentPosition, int *errorCode);

// gets next position
CircleList* getNext(CircleList* currentPosition, int* errorCode);

// prints the entire CircleList
void printCircleList(CircleList** currentPosition);