#include "sortingStationAlgorithm.h"
#include <stdlib.h>
#include "stack.h"
#include "advancedBracketBalance.h"

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

char* convertToPostfixForm(char infix[], int* errorCode)
{
    if (!areBracketsBalanced(infix, errorCode))
    {
        return NULL;
    }
    int lengthOfInfix = 0;
    for (int i = 0; infix[i] != '\0'; ++i)
    {
        ++lengthOfInfix;
    }
    char operations[5] = { '+', '*', '-', '/', '\0' };
    Stack* stack = createStack();
    char* postfix = calloc(lengthOfInfix, sizeof(char));
    if (postfix == NULL)
    {
        *errorCode = -11;
        return NULL;
    }
    int currentIndex = 0;
    for (int i = 0; i < lengthOfInfix; ++i)
    {
        int indexOfOperation = findElement(operations, infix[i]);
        if ( infix[i] >= '0' && infix[i] <= '9' )
        {
            postfix[currentIndex] = infix[i];
            ++currentIndex;
            postfix[currentIndex] = ' ';
            ++currentIndex;
        }
        else if (indexOfOperation != -1)
        {
            while (!stackIsEmpty(&stack) && (stack->value) != '(' &&
                    findElement(operations, stack->value) % 2 >= indexOfOperation % 2)
            {
                postfix[currentIndex] = pop(&stack, errorCode);
                ++currentIndex;
                postfix[currentIndex] = ' ';
                ++currentIndex;
                if (*errorCode != 0)
                {
                    free(postfix);
                    deleteStack(&stack);
                    return NULL;
                }
            }
            push(&stack, infix[i]);
        }
        else if (infix[i] == '(')
        {
            push(&stack, '(');
        }
        else if (infix[i] == ')')
        {
            while ((stack->value) != '(')
            {
                postfix[currentIndex] = pop(&stack, errorCode);
                ++currentIndex;
                postfix[currentIndex] = ' ';
                ++currentIndex;
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
        postfix[currentIndex] = pop(&stack, errorCode);
        ++currentIndex;
        postfix[currentIndex] = ' ';
        ++currentIndex;
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