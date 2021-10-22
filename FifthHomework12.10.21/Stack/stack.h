#pragma once
#include <stdbool.h>

typedef int Value;

typedef struct Stack
{
    Value value;
    struct Stack* next;
} Stack;

bool StackIsEmpty(Stack* stack);

int push(Stack* head, Value value);

int pop(Stack* head, int* errorCode);

int deleteStack(Stack* head);