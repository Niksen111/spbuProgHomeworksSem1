#pragma once
#include <stdbool.h>

// pointer to the first element of the list
typedef struct List List;

// pointer to a list item
typedef struct Position Position;

// returns true if the first line comes first in the lexicographical order
void changeValue(Position* position, int value);

// creates an empty list
List* createList();

// creates a NULL pointer of type Position
Position* createPosition();

// deletes the entire list
void deleteList(List* list);

// removes a pointer of type Position
void deletePosition(Position* position);

// adds an item to the list
void add(List** list, Position** position, int value);

// returns a pointer to the first position of the list
Position* getFirst(List* list);

// moves the pointer to the next element
void moveToNext(Position** position);

// checks if the current element is the last
bool isLast(Position* position);

// checks if the pointers are equal
bool arePointersEqual(Position* position1, Position* position2);

// returns true if the pointers are neighbors
bool areNeighbors(Position* currentPosition, Position* position);

// returns true if the list is empty
bool isListEmpty(List* list);

// returns value of the position
int getValue(Position* position);

// copies the pointer
Position* copyPointer(Position* position);