#include "sortingStationAlgorithm.h"
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int findElement(const char theArray[], const char element)
{
    for (int i = 0; theArray[i] != '\0'; ++i)
    {
        if (theArray[i] == element)
        {
            return i;
        }
    }
    return -1;
}

void addElementToPostfix(char postfix[], int *currentIndex,
                         Stack* stack, int* errorCode)
{
    postfix[*currentIndex] = pop(&stack, errorCode);
    ++currentIndex;
    postfix[*currentIndex] = ' ';
    ++currentIndex;
}

bool priorityFirstOverSecond(const char operations[], const int indexOfFirstOperation,
                      const int indexOfSecondOperation)
{
    return operations[indexOfFirstOperation] == '*'
        || operations[indexOfFirstOperation] == '/'
        || operations[indexOfSecondOperation] == '+'
        || operations[indexOfSecondOperation] == '-';
}

char *convertToPostfixForm(const char infix[], int *errorCode)
{
    const int lengthOfInfix = strlen(infix);
    const char operations[5] = {'+', '*', '-', '/', '\0'};
    Stack *stack = createStack();
    char *postfix = calloc(lengthOfInfix, sizeof(char));
    if (postfix == NULL)
    {
        *errorCode = -1;
        return NULL;
    }
    int currentIndex = 0;
    for (int i = 0; i < lengthOfInfix; ++i)
    {
        const int indexOfOperation = findElement(operations, infix[i]);
        if (infix[i] >= '0' && infix[i] <= '9')
        {
            addElementToPostfix(postfix, &currentIndex,
                                stack, errorCode);
        }
        else if (indexOfOperation != -1)
        {
            while (!stackIsEmpty(&stack) && stack->value != '(' &&
                    priorityFirstOverSecond(operations, stack->value, indexOfOperation))
            {
                addElementToPostfix(postfix, &currentIndex,
                                    stack, errorCode);
                if (*errorCode != 0)
                {
                    free(postfix);
                    deleteStack(&stack);
                    return NULL;
                }
            }
            *errorCode = push(&stack, infix[i]);
            if (*errorCode != 0)
            {
                free(postfix);
                deleteStack(&stack);
                return NULL;
            }
        }
        else if (infix[i] == '(')
        {
            *errorCode = push(&stack, '(');
            if (*errorCode != 0)
            {
                free(postfix);
                deleteStack(&stack);
                return NULL;
            }
        }
        else if (infix[i] == ')')
        {
            while ((stack->value) != '(')
            {
                addElementToPostfix(postfix, &currentIndex,
                                    stack, errorCode);
                if (*errorCode != 0)
                {
                    free(postfix);
                    deleteStack(&stack);
                    return NULL;
                }
            }
            pop(&stack, errorCode);
            if (*errorCode != 0)
            {
                free(postfix);
                deleteStack(&stack);
                return NULL;
            }
        }
    }
    while (!stackIsEmpty(&stack))
    {
        addElementToPostfix(postfix, &currentIndex,
                            stack, errorCode);
        if (*errorCode != 0)
        {
            free(postfix);
            deleteStack(&stack);
            return NULL;
        }
    }
    deleteStack(&stack);
    return postfix;
}