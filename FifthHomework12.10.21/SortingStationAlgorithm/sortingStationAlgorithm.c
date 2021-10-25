#include "sortingStationAlgorithm.h"
#include <stdlib.h>
#include "stack.h"
#include "advancedBracketBalance.h"

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
    char operations[4] = { '+', '-', '*', '/' };
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
        if ((int) infix[i] >= (int) '0' && (int) infix[i] <= (int) '9' ||
            infix[i] == ' ')
        {
            postfix[currentIndex] = infix[i];
            ++currentIndex;
        }
        else
        {
            return NULL;
        }
    }
}