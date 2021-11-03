#pragma once
#include <stdbool.h>

typedef struct Directory
{
    char* name;
    char* phoneNumber;
} Directory;

typedef struct ListElement
{
    Directory* directory;
    struct ListElement* next;
} ListElement;

typedef struct List
{
    ListElement* head;
} List;

typedef struct Position
{
    ListElement* position;
} Position;

typedef enum Priority
{
    name,
    phone
} Priority;

bool isFirstEarlier(char* first, char* second);

void changePriorityValue(Position* position, char* newValue, Priority priority);

List* createList();

Position* createPosition();

void deleteList(List* list);

void deletePosition(Position* position);

void add(List* list, Position* position, char* name, char* phone);

int lengthPartOfList(Position* start, Position* end);

Position* first(List* list);

Position* next(Position* position);

bool isLast(Position* position);

char* getPriorityValue(Position* position, Priority priority);