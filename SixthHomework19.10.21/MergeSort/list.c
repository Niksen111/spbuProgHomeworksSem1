#include "list.h"
#include <stdlib.h>
#include <string.h>

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


void changePriorityValue(Position* position, char* newValue, Priority priority)
{
    free(getPriorityValue(position, priority));
    if (priority == name)
    {
        position->position->directory->name = newValue;
    }
    else
    {
        position->position->directory->phoneNumber = newValue;
    }
}

List* createList()
{
    return calloc(1, sizeof(List));
}

Position* createPosition()
{
    return calloc(1, sizeof(Position));
}

void deleteList(List* list)
{
    ListElement* position = list->head;
    while (position != NULL)
    {
        list->head = list->head->next;
        free(position);
        position = list->head;
    }
    free(list);
}

void deletePosition(Position* position)
{
    free(position);
}

void addToHead(List* list, char* name, char* phone)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->directory->name = name;
    newElement->directory->phoneNumber = phone;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = list->head;
    list->head = newElement;
}

void addAfter(List* list, Position* position, char* name, char* phone)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->directory->name = name;
    newElement->directory->phoneNumber = phone;
    if (list->head == NULL)
    {
        list->head = newElement;
        position->position = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
    moveToNext(&position);
}

Position* getFirst(List* list)
{
    Position* positionFirst = createPosition();
    if (positionFirst == NULL)
    {
        return NULL;
    }
    positionFirst->position = list->head;
    return positionFirst;
}

Position* getLast(List* list)
{
    Position* positionLast = getFirst(list);
    while (!isLast(positionLast))
    {
        moveToNext(&positionLast);
    }
    return positionLast;
}

Position* getNext(Position* position)
{
    Position* newPosition = calloc(1, sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

void moveToNext(Position** position)
{
    if ((*position)->position == NULL)
    {
        return;
    }
    (*position)->position = (*position)->position->next;
}

bool isLast(Position* position)
{
    return position->position == NULL;
}

bool arePointersEqual(Position* position1, Position* position2)
{
    return position1->position == position2->position;
}

Position* copyPointer(Position* position)
{
    Position* newPosition = createPosition();
    if (newPosition == NULL)
    {
        return NULL;
    }
    newPosition->position = position->position;
    return newPosition;
}

void copyValues(Position** where, Position* from)
{
    (*where)->position->directory->name = from->position->directory->name;
    (*where)->position->directory->phoneNumber = from->position->directory->phoneNumber;
}

ListElement* getListElement(Position* position)
{
    return position->position;
}

Directory* getDirectory(List* list, Position* position)
{
    return position->position->directory;
}

char* getPriorityValue(Position* position, Priority priority)
{
    return priority == name ? position->position->directory->name :
           position->position->directory->phoneNumber;
}