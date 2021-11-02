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



List* createList();

void deleteList(List* list);

void deletePosition(Position* position);

void add(List* list, Position* position, char* name, char* phone);

Position* first(List* list);

Position* next(Position* position);

bool isLast(Position* position);

struct Directory* get(List* list, Position* position);