#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void fillWithZeros(char* line, int lineLength)
{
    for (int i = 0; i < lineLength; ++i)
    {
        line[i] = '\0';
    }
}

void moveCommentsToAnotherFile(const char fileNameFrom[], const char fileNameTo[])
{
    FILE* fileFrom = fopen(fileNameFrom, "r");
    if (fileFrom == NULL)
    {
        return;
    }
    FILE* fileTo = fopen(fileNameTo, "w");
    char* line = calloc(100, sizeof(char));
    if (line == NULL)
    {
        fclose(fileFrom);
        fclose(fileTo);
        return;
    }
    int index = 0;
    int state = 0;
    char c = '\0';
    while (fscanf(fileFrom, "%c", &c) >= 0)
    {
        switch (state)
        {
            case 0:
            {
                if (c == '"')
                {
                    state = 1;
                    line[index] = c;
                    ++index;
                }
                break;
            }
            case 1:
            {
                if (c == '"')
                {
                    state = 0;
                    line[index] = c;
                    index = 0;
                    fprintf(fileTo, "%s\n", line);
                    fillWithZeros(line, 100);
                    break;
                }
                line[index] = c;
                ++index;
            }
        }
    }
    fclose(fileFrom);
    fclose(fileTo);
    free(line);
}

bool testMoveCommentsToAnotherFile()
{
    moveCommentsToAnotherFile("input.txt", "output.txt");
    FILE* fileOutput = fopen("output.txt", "r");
    char line[100] = { 0 };
    fscanf(fileOutput, "%s", line);
    bool result = strcmp(line, "\"ksdjg\"") == 0;
    fscanf(fileOutput, "%s", line);
    result = result && strcmp(line, "\"sd\"") == 0;
    fscanf(fileOutput, "%s", line);
    result = result && strcmp(line, "\"lsdkf'sdlkf\"") == 0;
    fscanf(fileOutput, "%s", line);
    result = result && strcmp(line, "\"ksldfnvz235\"") == 0;
    fscanf(fileOutput, "%s", line);
    result = result && strcmp(line, "\"53kl\"") == 0;
    fclose(fileOutput);

    return result;
}

int main()
{
    if (!testMoveCommentsToAnotherFile())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    printf("All ok :)\n");
    return 0;
}
