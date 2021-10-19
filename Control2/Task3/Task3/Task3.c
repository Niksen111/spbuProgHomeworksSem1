#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void printArray(const int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%d ", theArray[i]);
    }
    printf("\n\n");
}

int lengthArrayFromFile(const char nameOfFile[], int* lengthOfArray)
{
    FILE* file = fopen(nameOfFile, "r");
    if (file == NULL)
    {
        return -1;
    }
    *lengthOfArray = 0;
    int temporary = 0;
    int readBytes = fscanf(file, "%d", &temporary);
    while (readBytes >= 0)
    {
        ++* lengthOfArray;
        readBytes = fscanf(file, "%d", &temporary);
    }
    fclose(file);
    return 0;
}

int readArrayFromFile(const char nameOfFile[], int theArray[], int lengthOfArray)
{
    FILE* file = fopen(nameOfFile, "r");
    if (file == NULL)
    {
        return -1;
    }
    for (int i = 0; i < lengthOfArray; ++i)
    {
        fscanf(file, "%d", &theArray[i]);
    }
    fclose(file);
    return 0;
}



int main()
{
    int lengthOfG = 0;
    if (lengthArrayFromFile("g.txt", &lengthOfG) == -1)
    {
        printf("File g.txt not found!");
        return -1;
    }
    if (lengthOfG != 1)
    {
        printf("File g.txt is incorrect!");
        return -1;
    }
    int numFromGFile = 0;
    if (readArrayFromFile("g.txt", &numFromGFile, 1) == -1)
    {
        printf("File g.txt not found!");
        return -1;
    }

    int lengthOfF = 0;
    if (lengthArrayFromFile("f.txt", &lengthOfG) == -1)
    {
        printf("File g.txt not found!");
        return -1;
    }

    int* arrayF = calloc(lengthOfF, sizeof(int));
    if (readArrayFromFile("f.txt", arrayF, lengthOfF) == -1)
    {
        printf("File g.txt not found!");
        return -1;
    }

    FILE* file = fopen("h.txt", "w");
    for (int i = 0; i < lengthOfF; ++i)
    {
        if (arrayF[i] < numFromGFile)
        {
            fprintf("h.txt", "%d ", arrayF[i]);
        }
    }
    fclose(file);
    free(arrayF);
}

