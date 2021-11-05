#include "sortedList.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct SortedList
{
    Value value;
    struct SortedList* next;
} SortedList;

SortedList* createSortedList()
{
    return NULL;
}

bool sortedListIsEmpty(SortedList** head)
{
    return *head == NULL;
}

SortedList* createNewElement(Value value, SortedList* next)
{
    SortedList* newElement = calloc(1, sizeof(SortedList));
    if (newElement == NULL)
    {
        return NULL;
    }
    newElement->value = value;
    newElement->next = next;
    return newElement;
}

int push(SortedList** head, Value value)
{
    if (sortedListIsEmpty(head) || (*head)->value >= value)
    {
        *head = createNewElement(value, *head);
        if (head == NULL)
        {
            return -1;
        }
        return 0;
    }
    SortedList* currentElement = *head;
    while (currentElement->next != NULL)
    {
        if (currentElement->next->value >= value)
        {
            currentElement->next = createNewElement(value, currentElement->next);
            return currentElement->next == NULL ? -1 : 0;
        }
        currentElement = currentElement->next;
    }
    currentElement->next = createNewElement(value, NULL);
    return currentElement->next == NULL ? -1 : 0;
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
    if (sortedListIsEmpty(head))
    {
        return -1;
    }
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
    printf("\n");
}

Value getValueFromHead(SortedList* head, int *errorCode)
{
    if (head == NULL)
    {

        *errorCode = -1;
        return 0;
    }
    return head->value;
}