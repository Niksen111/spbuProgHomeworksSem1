#include <stdio.h>
#include <stdbool.h>

bool isSubstring(char substring[], char string[])
{
    for (int i = 0; substring[i] != '\0'; ++i)
    {
        if (substring[i] != string[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    char string[10100] = { 0 };
    printf("Enter your string:\n");
    scanf("%s", string);

    char substring[10100] = { 0 };
    printf("Enter your substring:\n");
    scanf("%s", substring);

    int counterOfSubstringsInTheString = 0;

    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (isSubstring(substring, &string[i]))
        {
            ++counterOfSubstringsInTheString;
        }
    }

    printf("The number of the substrings in the string is %d.",
        counterOfSubstringsInTheString);
}
