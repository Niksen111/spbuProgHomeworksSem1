#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int convertToDecimal(char* line)
{
    const int length = strlen(line);
    int result = 0;
    int currentDegree = 1;
    for (int i = length - 1; i >= 0; --i)
    {
        result += (int)(line[i] - '0') * currentDegree;
        currentDegree *= 2;
    }
    return result;
}

bool testConvertToDecimal()
{
    char s1[100] = "0";
    char s2[100] = "101";
    char s3[100] = "100001";
    char s4[100] = "111111111";
    char s5[100] = "10101010101";

    return convertToDecimal(s1) == 0
        && convertToDecimal(s2) == 5
        && convertToDecimal(s3) == 33
        && convertToDecimal(s4) == 1023
        && convertToDecimal(s5) == 1365;
}

int main()
{
    if (testConvertToDecimal())
    {
        printf("Tests failed :(");
        return -1;
    }
    char line[33] = { 0 };
    while (true)
    {
        printf("Enter a binary number (no more than 32 characters):\n");
        printf("(enter \"exit\" if you want to end)\n");
        scanf("%s", line);
        if (strcmp("exit", line) == 0)
        {
            break;
        }
        else
        {
            printf("Decimal representation: %d\n", convertToDecimal(line));
        }
    }
    free(line);
    return 0;
}
