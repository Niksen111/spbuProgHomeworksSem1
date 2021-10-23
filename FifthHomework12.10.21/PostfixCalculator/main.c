#include <stdio.h>
#include "../Stack/stack.h"
#include "../Stack/stackTests.h"
#include "../Stack/stack.c"
#include "../Stack/stackTests.c"

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
            return value2 - value1;
        case (int) '*':
            return value1 * value2;
        case (int) '/':
            if (value2 == 0) *errorCode = -1;
            else return value2 / value1;
            return 0;
        default:
            *errorCode = -2;
            return 0;
    }
}

int postfixCalculator(char arraySymbols[], int* error)
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

bool testOperation()
{
    int errors[8] = { 0 };
    int answers[8] = { 0 };
    answers[0] = operation(4, 0, '/', &errors[0]);
    answers[1] = operation(4, 5, '#', &errors[1]);
    answers[2] = operation(-11, 7, '+', &errors[2]);
    answers[3] = operation(4, -5, '-', &errors[3]);
    answers[4] = operation(4, 0, '*', &errors[4]);
    answers[5] = operation(8, -2, '/', &errors[5]);
    answers[6] = operation(4, -5, '*', &errors[6]);
    answers[7] = operation(6, 5, '/', &errors[7]);


    return  answers[0] == 0 && errors[0] == -1 &&
            answers[1] == 0 && errors[1] == -2 &&
            answers[2] == -4 && errors[2] == 0 &&
            answers[3] == 9 && errors[3] == 0 &&
            answers[4] == 0 && errors[4] == 0 &&
            answers[5] == -4 && errors[5] == 0 &&
            answers[6] == -20 && errors[6] == 0 &&
            answers[7] == 1 && errors[7] == 0;
}

bool testPostfixCalculator()
{

}

int main() {
    if (!testStack() && !testOperation())
    {
        printf("Tests failed(\n");
        return 0;
    }
    int errorCode = 0;
    printf("Enter the numbers and operations with a space:\n");
    char postfixCalculatorEnter[1000] = { 0 };
    scanf("%[^\n]s", postfixCalculatorEnter);
    int result = postfixCalculator(postfixCalculatorEnter, &errorCode);
    handleTheError(errorCode);
    if (errorCode == 0)
    {
        printf("The result of all operations is %d", result);
    }
}
