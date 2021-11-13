#pragma once
#include <stdbool.h>

// pointer to the first element of the list
typedef struct List List;

// pointer to a list item
typedef struct Position Position;

//
typedef enum Priority
{
    name,
    phone
} Priority;

// returns true if the first line comes first in the lexicographical order
void changePriorityValue(Position* position, char* newValue, Priority priority);

// creates an empty list
List* createList();

// creates a NULL pointer of type Position
Position* createPosition();

// deletes the entire list
void deleteList(List* list);

// removes a pointer of type Position
void deletePosition(Position* position);

// adds an item to the list
void add(List** list, Position** position, char* name, char* phone);

// returns a pointer to the first position of the list
Position* first(List* list);

// returns a pointer to the last position of the list
Position* last(List* list);

// returns a pointer to the next element
Position* getNext(Position* position);

// moves the pointer to the next element
void moveToNext(Position** position);

// checks if the current element is the first
bool isFirst(Position* position, List* list);

// checks if the current element is the last
bool isLast(Position* position);

// checks if the pointers are equal
bool arePointersEqual(Position* position1, Position* position2);

// copies the values of one element to another
void copyValues(Position** where, Position* from);

//
char* getPriorityValue(Position* position, Priority priority);

// copies the pointer
Position* copyPointer(Position* position);