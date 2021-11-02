#include "list.h"
#include <stdlib.h>

List* createList()
{
    return calloc(1, sizeof(List));
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

void add(List* list, Position* position, char* name, char* phone)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    newElement->directory->name = name;
    newElement->directory->phoneNumber = phone;
    if (position->position == NULL)
    {
        list->head = newElement;
        return;
    }
    newElement->next = position->position->next;
    position->position->next = newElement;
}

Position* first(List* list)
{
    Position* positionFirst = calloc(1, sizeof(Position));
    positionFirst->position = list->head;
    return positionFirst;
}

Position* next(Position* position)
{
    Position* newPosition = calloc(1, sizeof(Position));
    newPosition->position = position->position->next;
    return newPosition;
}

bool isLast(Position* position)
{
    return position->position == NULL;
}

Directory* get(List* list, Position* position)
{
    return position->position->directory;
}