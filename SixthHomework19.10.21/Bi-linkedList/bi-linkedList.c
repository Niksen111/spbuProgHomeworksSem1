#include <stdbool.h>
#include <stdlib.h>
#include "bi-linkedList.h"

typedef struct Element
{
    int value;
    struct Element* next;
    struct Element* previous;
} Element;

typedef struct List
{
    Element* head;
    Element* tail;
} List;

typedef struct Position
{
    Element* position;
} Position;

List* createList()
{
    return calloc(1, sizeof(List));
}

Position* createPosition()
{
    return calloc(1, sizeof(Position));
}

bool isEnd(Position* position)
{
    return position->position->next == NULL;
}

void first(List* list, Position* position)
{
    position->position = list->head;
}

void last(List* list, Position* position)
{
    position->position = list->tail;
}

int next(Position* position) // �� ������ ��������� �� NULL
{
    if (position->position->next == NULL)
    {
        return -1;
    }
    position->position = position->position->next;
    return 0;
}

int previous(Position* position) // �� ������ ��������� �� NULL
{
    if (position->position->previous == NULL)
    {
        return -1;
    }
    position->position = position->position->previous;
    return 0;
}

void removeFirst(List* list, Position* position)
{

}

void removeLast(List* list, Position* position)
{

}

void remove(List* list, Position* position)
{
    if (position->position->next == NULL)
    {
        removeFirst(list, position);
        return;
    }
    if (position->position->previous == NULL)
    {
        removeLast(list, position);
        return;
    }
    position->position->previous->next = position->position->next;
    position->position->next->previous = position->position->previous;
}

void deletePosition(Position* position)
{
    free(position);
}

int value(Position* position)
{
    return position->position->value;
}

void setValue(Position* position, int value)
{
    position->position->value = value;
}

void addBefore(List* list, Position* position, int value)
{
    Element* newElement = calloc(1, sizeof(Element));
    newElement->value = value;
    position->position = position->position->previous;
    newElement->next = position->position;
    if (position->position != list->head)
    {
        position->position->previous->next = newElement;
    }
    else
    {
        list->head = newElement;
    }
    position->position->previous = newElement;
    position->position - newElement;
}

void addNext(List* list, Position* position, int value)
{
    Element* newElement = calloc(1, sizeof(Element));
    newElement->value = value;
    newElement->next = position->position->next;
    newElement->previous = position->position;
    if (position->position != list->tail)
    {
        position->position->next->previous = newElement;
    }
    else
    {
        list->tail = newElement;
    }
    position->position->next = newElement;
    position->position = newElement;
}
