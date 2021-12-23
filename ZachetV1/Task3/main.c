#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isCorrectGroupNumber(const char* line)
{
    int state = 0;
    int i = 0;
    while (true)
    {
        char c = line[i];
        ++i;
        switch (state)
        {
            case 0:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = 1;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 1:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = 2;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 2:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == '.')
                {
                    state = 3;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 3:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == 'B' || c == 'M' || c == 'S')
                {
                    state = 4;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 4:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = 5;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 5:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (isDigit(c))
                {
                    state = 6;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 6:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == '-')
                {
                    state = 7;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 7:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == 'm')
                {
                    state = 8;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 8:
            {
                if (c == '\0')
                {
                    return false;
                }
                if (c == 'm')
                {
                    state = 9;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 9:
            {
                if (c == '\0')
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

bool testIsCorrectGroupNumber()
{
    return isCorrectGroupNumber("21.B10-mm") && isCorrectGroupNumber("66.M33-mm")
        && isCorrectGroupNumber("13.S69-mm") && isCorrectGroupNumber("00.B00-mm")
        && !isCorrectGroupNumber("1.B10-mm") && !isCorrectGroupNumber("XX.S30-mm")
        && !isCorrectGroupNumber("45B30-mm") && !isCorrectGroupNumber("44.M31-mM")
        && !isCorrectGroupNumber("666.B1337-mm") && !isCorrectGroupNumber("21.B10-mmm")
        && !isCorrectGroupNumber("") && !isCorrectGroupNumber("35.M");
}

int main()
{
    if (!testIsCorrectGroupNumber())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    char* line[1000] = { 0 };
    while (true)
    {
        printf("Enter the group number without spaces:\n");
        printf("(enter \"exit\" if you want to end)\n");
        scanf("%s", line);
        if (strcmp("exit", line) == 0)
        {
            break;
        }
        if (isCorrectGroupNumber(line))
        {
            printf("This is the correct group number :)\n");
        }
        else
        {
            printf("This is not the correct group number :(\n");
        }
    }
    free(line);
    return 0;
}
