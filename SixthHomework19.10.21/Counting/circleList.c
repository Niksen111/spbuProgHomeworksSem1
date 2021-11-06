#include "circleList.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct CircleList
{
    Value value;
    struct CircleList* next;
} CircleList;

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
    *currentPosition = (*currentPosition)->next;
}

void switchToN(CircleList** currentPosition, int n)
{
    for (int i = 0; i < n; ++i)
    {
        switchToNext(currentPosition);
    }
}

int popNext(CircleList** currentPosition, int* errorCode)
{
    if ((*currentPosition) == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    Value returnedValue = ((*currentPosition)->next->value);
    if ((*currentPosition) == (*currentPosition)->next)
    {
        free(*currentPosition);
        *currentPosition = NULL;
        return returnedValue;
    }
    CircleList* deletedPosition = (*currentPosition)->next;
    (*currentPosition)->next = (*currentPosition)->next->next;
    free(deletedPosition);
    return returnedValue;
}

void deleteCircleList(CircleList** currentPosition)
{
    while (!circleListIsEmpty(currentPosition))
    {
        int errorCode = 0;
        popNext(currentPosition, &errorCode);
    }
}

Value getCurrentPositionValue(CircleList* currentPosition, int *errorCode)
{
    *errorCode = 0;
    if (currentPosition == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    return currentPosition->value;
}

CircleList* getNext(CircleList* currentPosition, int* errorCode)
{
    *errorCode = 0;
    if (currentPosition == NULL)
    {
        *errorCode = -1;
        return NULL;
    }
    return currentPosition->next;
}

void printCircleList(CircleList** currentPosition)
{
    CircleList* list = (*currentPosition)->next;
    while (list != *currentPosition)
    {
        printf("%d ", list->value);
        switchToNext(&list);
    }
    printf("%d\n", ((*currentPosition)->value));
}