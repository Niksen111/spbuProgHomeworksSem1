#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct ListElement
{
    int value;
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


void changeValue(Position* position, int newValue)
{
    position->position->value = newValue;
}

List* createList()
{
    return calloc(1, sizeof(List));
}

Position* createPosition()
{
    return calloc(1, sizeof(Position));
}

void deleteList(List** list)
{
    ListElement* position = (*list)->head;
    while (position != NULL)
    {
        (*list)->head = (*list)->head->next;
        free(position);
        position = (*list)->head;
    }
    free(*list);
    (*list) = NULL;
}

void deletePosition(Position** position)
{
    free(*position);
    (*position) = NULL;
}

void addToHead(List* list, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = list->head;
    list->head = newElement;
}

void addAfter(List* list, Position* position, int value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (list->head == NULL)
    {
        list->head = newElement;
        position->position = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

Position* getFirst(List* list)
{
    Position* positionFirst = createPosition();
    positionFirst->position = list->head;
    return positionFirst;
}

void moveToNext(Position* position)
{
    if (position->position == NULL)
    {
        return;
    }
    position->position = position->position->next;
}

bool isLast(Position* position)
{
    return position->position == NULL
            || position->position->next == NULL;
}

bool arePositionEqual(Position* position1, Position* position2)
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

bool areNeighbors(Position* currentPosition, Position* position)
{
    return currentPosition->position->next == position->position
            || position->position->next == currentPosition->position;
}

bool isListEmpty(List* list)
{
    if (list == NULL)
    {
        return true;
    }
    return list->head == NULL;
}

int getValue(Position* position)
{
    if (position == NULL || position->position == NULL)
    {
        return -666;
    }
    return position->position->value;
}