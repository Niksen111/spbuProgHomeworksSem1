#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct ListElement
{
    char* value;
    int counter;
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


void changeValue(Position* position, char* newValue)
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

void deleteList(List* list)
{
    ListElement* element = list->head;
    while (element != NULL)
    {
        list->head = list->head->next;
        free(element);
        element = list->head;
    }
}

void deletePosition(Position** position)
{
    free(*position);
    *position = NULL;
}

void addToHead(List* list, char* value)
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

void addAfter(List* list, Position* position, char* value)
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
    return position->position->next == NULL;
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

char* getValue(Position* position)
{
    return position->position->value;
}

bool isListEmpty(List* list)
{
    return list->head == NULL;
}

void increaseCounter(Position* position)
{
    position->position->counter += 1;
}