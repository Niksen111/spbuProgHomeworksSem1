#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

typedef enum States
{
    zero,
    first,
    second,
    third,
    fourth,
    fifth,
    sixth
} States;

bool isRealNumber(const char* number)
{
    States state = zero;
    int i = 0;
    while (true)
    {
        char c = number[i];
        ++i;
        switch (state)
        {
            case zero:
            {
                
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = first;
                }
                else
                {
                    return false;
                }
                break;
            }
            case first:
            {
                if (c == '\0')
                {
                    return true;
                }
                if (isDigit(c))
                {
                    state = first;
                }
                else if (c == '.')
                {
                    state = second;
                }
                else if (c == 'e')
                {
                    state = fourth;
                }
                else
                {
                    return false;
                }
                break;
            }
            case second:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = third;
                }
                else
                {
                    return false;
                }
                break;
            }
            case third:
            {
                if (c == '\0')
                {
                    return true;
                }
                if (isDigit(c))
                {
                    state = third;
                }
                else if (c == 'e')
                {
                    state = fourth;
                }
                else
                {
                    return false;
                }
                break;
            }
            case fourth:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == '+' || c == '-')
                {
                    state = fifth;
                }
                else if (isDigit(c))
                {
                    state = sixth;
                }
                else
                {
                    return false;
                }
                break;
            }
            case fifth:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = sixth;
                }
                else
                {
                    return false;
                }
                break;
            }
            case sixth:
            {
                if (c == '\0')
                {
                    return true;
                }
                if (isDigit(c))
                {
                    state = sixth;
                }
                else
                {
                    return false;
                }
                break;
            }
        }
    }
}

bool testIsRealNumber()
{
    return isRealNumber("1543345665") && isRealNumber("0")
        && !isRealNumber("") && !isRealNumber("12423.")
        && isRealNumber("142423.3435") && isRealNumber("1324.2")
        && !isRealNumber("1234e") && !isRealNumber("3132e+")
        && !isRealNumber("3241e-") && isRealNumber("2423e+233")
        && isRealNumber("23423e-1") && !isRealNumber("2134.2332e")
        && !isRealNumber("1523.e") && !isRealNumber("15665.e-")
        && !isRealNumber("15433.34e") && isRealNumber("665.243e-5")
        && isRealNumber("3235.323e534") && isRealNumber("213.12323e-434")
        && !isRealNumber("23434.324e-324e") && !isRealNumber("234e.324")
        && !isRealNumber("32434.43e+3434i");
}

int main()
{
    if (!testIsRealNumber())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    char* line = calloc(1000, sizeof(char));
    while (true)
    {
        printf("Enter the text without spaces:\n");
        printf("(enter \"exit\" if you want to end)\n");
        scanf("%s", line);
        if (strcmp("exit", line) == '\0')
        {
            break;
        }
        if (isRealNumber(line))
        {
            printf("This is a real number :)\n");
        }
        else
        {
            printf("This isn't a real number :(\n");
        }
    }
    free(line);
    return 0;
}
