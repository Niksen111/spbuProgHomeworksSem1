#pragma once
#include <stdbool.h>

//
typedef struct Directory Directory;

//
typedef struct ListElement ListElement;

//
typedef struct List List;

//
typedef struct Position Position;

//
typedef enum Priority
{
    name,
    phone
} Priority;

//
bool isFirstEarlier(char* first, char* second);

//
void changePriorityValue(Position* position, char* newValue, Priority priority);

//
List* createList();

//
Position* createPosition();

//
void deleteList(List* list);

//
void deletePosition(Position* position);

//
void add(List* list, Position* position, char* name, char* phone);

//
int lengthPartOfList(Position* start, Position* end);

//
Position* first(List* list);

//
Position* next(Position* position);

//
bool isLast(Position* position);

//
ListElement* getListElement(Position* position);

//
Directory* getDirectory(List* list, Position* position);

//
char* getPriorityValue(Position* position, Priority priority);