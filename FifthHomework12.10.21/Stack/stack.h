#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Stack
{
    Value value;
    struct Stack* next;
} Stack;

Stack* createStack();

bool stackIsEmpty(Stack** head);

int push(Stack** head, Value value);

Value pop(Stack** head, int* errorCode);

int deleteStack(Stack** head);

void printStack(Stack** head);