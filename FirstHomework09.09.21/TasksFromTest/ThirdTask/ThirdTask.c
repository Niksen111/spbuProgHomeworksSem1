#include <stdio.h>
#include <string.h>

// Function that returns the index of the symbol if it is in the array
int symbolInArray(char symbol, char array[], int lengthOfArray)
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        if (array[i] == symbol)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    char theString[10100] = { 0 };
    printf("%s\n", "Enter your string (less then 10000 symbols)");
    scanf("%s", theString);

    // All types of open and closed brackets
    const char openingBrackets[4] = { '(', '[', '{', '<' };
    const char closingBrackets[4] = { ')', ']', '}', '>' };

    // In this array we will store the open brackets
    char brackets[10100] = { 0 };
    int indexOfBrackets = 0;

    for (int i = 0; theString[i] != '\0'; ++i)
    {
        // If the current symbol is an open bracket 
        // that we put it in brackets array
        if (symbolInArray(theString[i], openingBrackets, sizeof(openingBrackets)) != -1)
        {
            brackets[indexOfBrackets] = theString[i];
            ++indexOfBrackets;
        }
        // If the current symbol is a closed bracket 
        else if (symbolInArray(theString[i], closingBrackets, 4) != -1)
        {
            // If the last open bracket and the current closed bracket
            // are the same 
            if (brackets[indexOfBrackets - 1] ==
                openingBrackets[symbolInArray(theString[i], closingBrackets, sizeof(closingBrackets))])
            {
                // We remove the last open bracket from the bracket array
                --indexOfBrackets;
                brackets[indexOfBrackets] = '\0';
            }
            else
            {
                printf("Balance of brackets is off :(");
                return 0;
            }
        }
    }

    // Check that all brackets are closed
    if (indexOfBrackets != 0)
    {
        printf("Balance of brackets is off:(");
    }
    else
    {
        printf("Balance of brackets is ok :)");
    }
}
