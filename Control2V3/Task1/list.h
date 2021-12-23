#pragma once
#include <stdbool.h>

// pointer to the first element of the list
typedef struct List List;

// pointer to a list item
typedef struct Position Position;

// changes value of the position
void changeValue(Position* position, int value);

// creates an empty list
List* createList();

// creates a NULL pointer of type Position
Position* createPosition();

// deletes the entire list
void deleteList(List** list);

// removes a Position
void deletePosition(Position** position);

// adds an item to the head of the list
void addToHead(List* list, int value);

// adds an item after the position to the list
void addAfter(List* list, Position* position, int value);

// returns first position of the list
Position* getFirst(List* list);

// moves the position to the next element
void moveToNext(Position* position);

// checks if the current element is the last
bool isLast(Position* position);

// checks if the position are equal
bool arePositionEqual(Position* position1, Position* position2);

// returns true if the pointers are neighbors
bool areNeighbors(Position* currentPosition, Position* position);

// returns true if the list is empty
bool isListEmpty(List* list);

// returns value of the position
int getValue(Position* position);

// copies the pointer
Position* copyPointer(Position* position);