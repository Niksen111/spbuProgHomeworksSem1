#include "circleList.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct CircleListRoot
{
    Value value;
    struct CircleListRoot* next;
} CircleList;

CircleListRoot* createCircleList()
{
    return NULL;
}

bool circleListIsEmpty(CircleListRoot* currentPosition)
{
    return currentPosition == NULL;
}

int push(CircleListRoot** currentPosition, Value value)
{
    CircleListRoot* newElement = calloc(1, sizeof(CircleList));
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

void switchRootToNext(CircleListRoot** currentPosition)
{
    *currentPosition = (*currentPosition)->next;
}

void moveNPositionsForward(CircleListRoot** currentPosition, int n)
{
    for (int i = 0; i < n; ++i)
    {
        switchRootToNext(currentPosition);
    }
}

int popNext(CircleListRoot** currentPosition, int* errorCode)
{
    if ((*currentPosition) == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    Value returnedValue = (*currentPosition)->next->value;
    if (*currentPosition == (*currentPosition)->next)
    {
        free(*currentPosition);
        *currentPosition = NULL;
        return returnedValue;
    }
    CircleListRoot* deletedPosition = (*currentPosition)->next;
    (*currentPosition)->next = (*currentPosition)->next->next;
    free(deletedPosition);
    return returnedValue;
}

void deleteCircleList(CircleListRoot** currentPosition)
{
    while (!circleListIsEmpty(*currentPosition))
    {
        int errorCode = 0;
        popNext(currentPosition, &errorCode);
    }
}

Value getCurrentPositionValue(CircleListRoot* currentPosition, int *errorCode)
{
    *errorCode = 0;
    if (currentPosition == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    return currentPosition->value;
}

CircleListRoot* getNext(CircleListRoot* currentPosition, int* errorCode)
{
    *errorCode = 0;
    if (currentPosition == NULL)
    {
        *errorCode = -1;
        return NULL;
    }
    return currentPosition->next;
}

void printCircleList(CircleListRoot* currentPosition)
{
    CircleListRoot* list = currentPosition->next;
    while (list != currentPosition)
    {
        printf("%d ", list->value);
        switchRootToNext(&list);
    }
    printf("%d\n", currentPosition->value);
}