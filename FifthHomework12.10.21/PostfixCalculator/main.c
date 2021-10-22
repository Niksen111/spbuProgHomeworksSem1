#include <stdio.h>
#include "../Stack/stack.h"
#include "../Stack/stackTests.h"

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
    switch(operation)
    {
        case (int) '+':
            return value1 + value2;
        case (int) '-':
            return value1 - value2;
        case (int) '*':
            return value1 * value2;
        case (int) '/':
            if (value2 == 0) *errorCode = -1;
            else return value1 / value2;
        default:
            *errorCode = -2;
            return 0;
    }
}

int postfixCalculator(int* error)
{
    error = 0;
    Stack* stack = createStack();
    int symbol = 0;
    while(scanf("%d", &symbol) != EOF)
    {
        if (symbol >= 0 && symbol <= 9)
        {
            push(&stack, symbol);
        }
        else
        {
            int errorCode = 0;
            int value1 = pop(&stack, &errorCode);
            if (errorCode != 0)
            {
                *error = -4;
                deleteStack(&stack);
                return -1;
            }
            int value2 = pop(&stack, &errorCode);
            if (errorCode != 0)
            {
                *error = -4;
                deleteStack(&stack);
                return -1;
            }
            int result = operation(value1, value2, symbol, &errorCode);
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

int main() {
    if (!testStack())
    {
        printf("Tests failed(\n");
        return 0;
    }
    int errorCode = 0;
    printf("Enter the numbers and operations with a space.\n");
    int result = postfixCalculator(&errorCode);
    handleTheError(errorCode);
    if (errorCode == 0)
    {
        printf("The result of all operations is %d", result);
    }
}
