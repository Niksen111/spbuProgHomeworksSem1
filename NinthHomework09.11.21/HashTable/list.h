#pragma once
#include <stdbool.h>

// pointer to the first element of the list
typedef struct List List;

// pointer to a list item
typedef struct Position Position;

// returns true if the first line comes first in the lexicographical order
void changeValue(Position* position, char* newValue);

// creates an empty list
List* createList();

// creates a NULL pointer of type Position
Position* createPosition();

// deletes the entire list
void deleteList(List* list);

// removes a pointer of type Position
void deletePosition(Position** position);

// adds an item to the head of the list
void addToHead(List* list, char* value);

// adds an item to the list
void addAfter(List* list, Position* position, char* value);

// returns a pointer to the first position of the list
Position* getFirst(List* list);

// returns a pointer to the last position of the list
Position* getLast(List* list);

// moves the pointer to the next element
void moveToNext(Position** position);

// checks if the current element is the first
bool isFirst(Position* position, List* list);

// checks if the current element is the last
bool isLast(Position* position);

// checks if the pointers are equal
bool arePointersEqual(Position* position1, Position* position2);

// returns priority value
char* getValue(Position* position);

// copies the pointer
Position* copyPointer(Position* position);

// returns true if the list is empty
bool isListEmpty(List* list);