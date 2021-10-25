#pragma once
#include <stdbool.h>

// type of data that will be stored in the stack
typedef int Value;

// stack structure
typedef struct Stack
{
    Value value;
    struct Stack* next;
} Stack;

// created an empty stack
Stack* createStack();

// checks if the stack is empty
bool stackIsEmpty(Stack** head);

// adds an element to the head of the stack
int push(Stack** head, Value value);

// removes an element form the head of the stack and returns it
Value pop(Stack** head, int* errorCode);

// removes the entire stack
void deleteStack(Stack** head);

// prints the entire stack
void printStack(Stack** head);