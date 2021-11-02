#include "circleList.h"
#include <stdlib.h>
#include <stdio.h>

CircleList* createCircleList()
{
    return NULL;
}

bool circleListIsEmpty(CircleList** currentPosition)
{
    return *currentPosition == NULL;
}

int push(CircleList** currentPosition, Value value)
{
    CircleList* newElement = calloc(1, sizeof(CircleList));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = value;
    if (*currentPosition == NULL)
    {
        newElement->next = newElement;
        *currentPosition = newElement;
        return 0;
    }
    newElement->next = (*currentPosition)->next;
    (*currentPosition)->next = newElement;
    *currentPosition = newElement;
    return 0;
}

void switchToNext(CircleList** currentPosition)
{
    (*currentPosition) = (*currentPosition)->next;
}

int popCurrent(CircleList** currentPosition, int* errorCode)
{
    if ((*currentPosition) == NULL)
    {
        return 0;
    }
    if ((*currentPosition) == (*currentPosition)->next)
    {
        free(*currentPosition);
        return 0;
    }
    CircleList* deletedPosition = (*currentPosition);
    switchToNext(currentPosition);
    free(deletedPosition);
    return 0;
}

void deleteCircleList(CircleList** currentPosition)
{
    while (!circleListIsEmpty(currentPosition))
    {
        int errorCode = 0;
        popCurrent(currentPosition, &errorCode);
    }
}

void printCircleList(CircleList** currentPosition)
{
    CircleList* list = (*currentPosition)->next;
    while (list != *currentPosition)
    {
        printf("%d ", (list->value));
        switchToNext(&list);
    }
    printf("\n");
}