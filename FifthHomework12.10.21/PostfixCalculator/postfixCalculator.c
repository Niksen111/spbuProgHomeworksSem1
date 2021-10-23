#include "postfixCalculator.h"
#include "../Stack/stack.h"
#include <stdio.h>

void handleTheError(int errorCode)
{
    switch (errorCode)
    {
        case -1:
            printf("Dividing by 0.\n");
            return;
        case -2:
            printf("The entered character is wrong.\n");
            return;
        case -3:
            printf("There are unused numbers left over.\n");
            return;
        case -4:
            printf("Not enough numbers to perform the operation.\n");
            return;
        default:
            return;
    }
}

int operation(int value1, int value2, int operation, int* errorCode)
{
    *errorCode = 0;
    switch (operation)
    {
        case (int) '+':
            return value1 + value2;
        case (int) '-':
            return value1 - value2;
        case (int) '*':
            return value1 * value2;
        case (int) '/':
            if (value2 == 0)
            {
                *errorCode = -1;
            }
            else
            {
                return value1 / value2;
            }
            return 0;
        default:
            *errorCode = -2;
            return 0;
    }
}

int postfixCalculator(const char arraySymbols[], int* error)
{
    *error = 0;
    Stack* stack = createStack();
    for (int i = 0; arraySymbols[i] != '\0'; ++i)
    {
        if (arraySymbols[i] == ' ')
        {
            continue;
        }
        if ((int) arraySymbols[i] >= (int) '0' && (int) arraySymbols[i] <= (int) '9')
        {
            push(&stack, (int) arraySymbols[i] - (int) '0');
        }
        else
        {
            int errorCode = 0;
            int value2 = pop(&stack, &errorCode);
            if (errorCode != 0)
            {
                *error = -4;
                deleteStack(&stack);
                return 0;
            }
            int value1 = pop(&stack, &errorCode);
            if (errorCode != 0)
            {
                *error = -4;
                deleteStack(&stack);
                return 0;
            }
            int result = operation(value1, value2, arraySymbols[i], &errorCode);
            if (errorCode == -1)
            {
                *error = -1;
                deleteStack(&stack);
                return 0;
            }
            if (errorCode == -2)
            {
                *error = -2;
                deleteStack(&stack);
                return 0;
            }
            push(&stack, result);
        }
    }
    if ((stack->next) != NULL)
    {
        *error = -3;
        deleteStack(&stack);
        return 0;
    }
    int result = stack->value;
    deleteStack(&stack);
    return result;
}