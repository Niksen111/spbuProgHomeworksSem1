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
        char c = 0;
        switch (state)
        {
            case 0:
            {
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
                c = line[i];
                ++i;
                if (c == 0)
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
    char s1[100] = "21.B10-mm";
    char s2[100] = "66.M33-mm";
    char s3[100] = "13.S69-mm";
    char s4[100] = "00.B00-mm";
    char s5[100] = "1.B10-mm";
    char s6[100] = "XX.S30-mm";
    char s7[100] = "45B30-mm";
    char s8[100] = "44.M31-mM";
    char s9[100] = "666.B1337-mm";
    char s10[100] = "21.B10-mmm";
    char s11[100] = "";
    char s12[100] = "35.M";

    return isCorrectGroupNumber(s1) && isCorrectGroupNumber(s2)
        && isCorrectGroupNumber(s3) && isCorrectGroupNumber(s4)
        && !isCorrectGroupNumber(s5) && !isCorrectGroupNumber(s6)
        && !isCorrectGroupNumber(s7) && !isCorrectGroupNumber(s8)
        && !isCorrectGroupNumber(s9) && !isCorrectGroupNumber(s10)
        && !isCorrectGroupNumber(s11) && !isCorrectGroupNumber(s12);
}

int main()
{
    if (!testIsCorrectGroupNumber())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    char* line = calloc(1000, sizeof(char));
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
