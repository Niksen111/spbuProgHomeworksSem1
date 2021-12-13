#pragma once
#include <stdbool.h>

// type of data that will be stored in the CircleList
typedef int Value;

// CircleList structure
typedef struct CircleListRoot CircleListRoot;

// created an empty CircleList
CircleListRoot* createCircleList();

// checks if the CircleList is empty
bool circleListIsEmpty(CircleListRoot* root);

// adds an element after the current to the CircleList
int push(CircleListRoot** root, Value value);

// Moves the pointer to the next element
void switchRootToNext(CircleListRoot** root);

// moves the pointer to n elements
void moveNPositionsForward(CircleListRoot** root, int n);

// removes the current element and moves the pointer to the next
int popNext(CircleListRoot** root, int* errorCode);

// removes the entire CircleList
void deleteCircleList(CircleListRoot** root);

// gets value from current position of CircleList
Value getCurrentPositionValue(CircleListRoot* root, int *errorCode);

// gets next position
CircleListRoot* getNext(CircleListRoot* root, int* errorCode);

// prints the entire CircleList
void printCircleList(CircleListRoot* root);