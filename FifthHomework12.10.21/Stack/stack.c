#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* createStack()
{
    return NULL;
}

bool stackIsEmpty(Stack** head)
{
    return *head == NULL;
}

int push(Stack** head, Value value)
{
    Stack* newElement = calloc(1, sizeof(Stack));
    if (newElement == NULL)
    {
        return -1;
    }
    newElement->value = value;
    newElement->next = *head;
    *head = newElement;
    return 0;
}

Value pop(Stack** head, int* errorCode)
{
    if (*head == NULL)
    {
        *errorCode = -1;
        return 0;
    }
    *errorCode = 0;
    Stack* deletableElement = *head;
    Value value = (*head)->value;
    *head = (*head)->next;
    free(deletableElement);
    return value;
}

void deleteStack(Stack** head)
{
    while (!stackIsEmpty(head))
    {
        int errorCode = 0;
        pop(head, &errorCode);
    }
}

void printStack(Stack** head)
{
    Stack* stack = *head;
    while (!stackIsEmpty(&stack))
    {
        printf("%d ", (stack->value));
        stack = stack->next;
    }
}