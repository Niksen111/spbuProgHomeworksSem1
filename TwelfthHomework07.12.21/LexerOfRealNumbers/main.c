#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isRealNumber(const char* number)
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
                c = number[i];
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
                c = number[i];
                ++i;
                if (c == 0)
                {
                    return true;
                }
                if (isDigit(c))
                {
                    state = 1;
                }
                else if (c == '.')
                {
                    state = 2;
                }
                else if (c == 'e')
                {
                    state = 4;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 2:
            {
                c = number[i];
                ++i;
                if (c == 0)
                {
                    return false;
                }
                if (isDigit(c))
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
                c = number[i];
                ++i;
                if (c == 0)
                {
                    return true;
                }
                if (isDigit(c))
                {
                    state = 3;
                }
                else if (c == 'e')
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
                c = number[i];
                ++i;
                if (c == 0)
                {
                    return false;
                }
                if (c == '+' || c == '-')
                {
                    state = 5;
                }
                else if (isDigit(c))
                {
                    state = 6;
                }
                else
                {
                    return false;
                }
                break;
            }
            case 5:
            {
                c = number[i];
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
                c = number[i];
                ++i;
                if (c == 0)
                {
                    return true;
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
        }
    }
}

bool testIsRealNumber()
{
    char s1[100] = "1543345665";
    char s2[100] = "0";
    char s3[100] = "";
    char s4[100] = "12423.";
    char s5[100] = "142423.3435";
    char s6[100] = "1324.2";
    char s7[100] = "1234e";
    char s8[100] = "3132e+";
    char s9[100] = "3241e-";
    char s10[100] = "2423e+233";
    char s11[100] = "23423e-1";
    char s12[100] = "2134.2332e";
    char s13[100] = "1523.e";
    char s14[100] = "15665.e-";
    char s15[100] = "15433.34e";
    char s16[100] = "665.243e-5";
    char s17[100] = "3235.323e534";
    char s18[100] = "213.12323e-434";
    char s19[100] = "23434.324e-324e";
    char s20[100] = "234e.324";
    char s21[100] = "32434.43e+3434i";

    return isRealNumber(s1) && isRealNumber(s2)
        && !isRealNumber(s3) && !isRealNumber(s4)
        && isRealNumber(s5) && isRealNumber(s6)
        && !isRealNumber(s7) && !isRealNumber(s8)
        && !isRealNumber(s9) && isRealNumber(s10)
        && isRealNumber(s11) && !isRealNumber(s12)
        && !isRealNumber(s13) && !isRealNumber(s14)
        && !isRealNumber(s15) && isRealNumber(s16)
        && isRealNumber(s17) && isRealNumber(s18)
        && !isRealNumber(s19) && !isRealNumber(s20)
        && !isRealNumber(s21);
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
        if (strcmp("exit", line) == 0)
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
