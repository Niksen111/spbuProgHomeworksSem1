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

// head and tail of the CircleList
typedef struct BoardersOfCircleList
{
    CircleList* head;
    CircleList* tail;
} BoardersOfCircleList;

// created an empty CircleList
CircleList* createCircleList();

// created an empty BoardersOfCircleList
BoardersOfCircleList* createBoardersOfCircleList();

// checks if the CircleList is empty
bool circleListIsEmpty(CircleList** head);

// adds an element to the CircleList
int push(CircleList** head, Value value);

// removes an element form the head of the CircleList and returns it
Value removeItemFromHead(CircleList** head, int* errorCode);

// removes the entire CircleList
void deleteCircleList(CircleList** head);

// prints the entire CircleList
void printCircleList(CircleList** head); 