#include "sortedList.h"
#include <stdlib.h>
#include <stdio.h>

SortedList* createSortedList()
{
    return NULL;
}

bool sortedListIsEmpty(SortedList** head)
{
    return *head == NULL;
}

int push(SortedList** head, Value value)
{
    if ((*head)->value >= value)
    {
        SortedList* newElement = calloc(1, sizeof(SortedList));
        if (newElement == NULL)
        {
            return -1;
        }
        newElement->value = value;
        newElement->next = *head;
        *head = newElement;
        return 0;
    }
    SortedList* currentElement = *head;
    while (currentElement->next != NULL)
    {
        if (currentElement->next->value >= value)
        {
            SortedList* newElement = calloc(1, sizeof(SortedList));
            if (newElement == NULL)
            {
                return -1;
            }
            newElement->value = value;
            newElement->next = currentElement->next;
            currentElement->next = newElement;
            return 0;
        }
        currentElement = currentElement->next;
    }
    SortedList* newElement = calloc(1, sizeof(SortedList));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = value;
    newElement->next = NULL;
    currentElement->next = newElement;
    return 0;
}

Value removeItemFromHead(SortedList** head, int* errorCode)
{
    if (*head == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    *errorCode = 0;
    SortedList* deletableElement = *head;
    Value value = (*head)->value;
    *head = (*head)->next;
    free(deletableElement);
    return value;
}

int removeTheItem(SortedList** head, Value value)
{
    SortedList* currentElement = *head;
    if ((*head)->value == value)
    {
        *head = (*head)->next;
        free(currentElement);
        return 0;
    }
    while (currentElement->next != NULL)
    {
        if (currentElement->next->value == value)
        {
            SortedList* deletableItem = currentElement->next;
            currentElement->next = currentElement->next->next;
            free(deletableItem);
            return 0;
        }
        currentElement = currentElement->next;
    }
    return -1;
}

void deleteSortedList(SortedList** head)
{
    while (!sortedListIsEmpty(head))
    {
        int errorCode = 0;
        removeItemFromHead(head, &errorCode);
    }
}

void printSortedList(SortedList** head)
{
    SortedList* list = *head;
    while (!sortedListIsEmpty(&list))
    {
        printf("%d ", (list->value));
        list = list->next;
    }
}