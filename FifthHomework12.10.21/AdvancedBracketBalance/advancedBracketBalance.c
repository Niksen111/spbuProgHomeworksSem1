#include "advancedBracketBalance.h"
#include "../Stack/stack.h"
#include <stdio.h>

int findCharacter(const char list[], const char character)
{
    for (int i = 0; list[i] != '\0'; ++i)
    {
        if (list[i] == character)
        {
            return i;
        }
    }
    return -1;
}

void handleTheBracketError(const int errorCode)
{
    switch (errorCode)
    {
        case -1:
            printf("Closing parenthesis did not close anything.\n");
            return;
        case -2:
            printf("Mismatch between opening and closing parentheses.\n");
            return;
        case -3:
            printf("Not all brackets are closed.\n");
            return;
        default:
            return;
    }
}

bool areBracketsBalanced(const char listCharacters[], int *errorCode)
{
    *errorCode = 0;
    Stack* stackBrackets = createStack();
    char brackets[7] = { '(', ')', '[', ']', '{', '}', '\0' };
    for (int i = 0; listCharacters[i] != '\0'; ++i)
    {
        int indexCurrentCharacter = findCharacter(brackets, listCharacters[i]);
        if (indexCurrentCharacter == -1)
        {
            continue;
        }
        // if the current bracket is opening
        if (indexCurrentCharacter % 2 == 0)
        {
            push(&stackBrackets, listCharacters[i]);
        }
        else
        {
            if (stackIsEmpty(&stackBrackets))
            {
                *errorCode = -1;
                deleteStack(&stackBrackets);
                return false;
            }
            if ((stackBrackets->value) == brackets[indexCurrentCharacter - 1])
            {
                int error = 0;
                pop(&stackBrackets, &error);
                if (error != 0)
                {
                    *errorCode = -4;
                    return false;
                }
            }
            else
            {
                *errorCode = -2;
                deleteStack(&stackBrackets);
                return false;
            }
        }
    }
    if (!stackIsEmpty(&stackBrackets))
    {
        *errorCode = -3;
        deleteStack(&stackBrackets);
        return false;
    }
    deleteStack(&stackBrackets);
    return true;
}
