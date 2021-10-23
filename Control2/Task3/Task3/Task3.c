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

bool checkThatAnArraysAreIdentical(const int firstArray[],
    const int secondArray[], const int lengthOfArrays)
{
    for (int i = 0; i < lengthOfArrays; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
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

bool testLengthArrayFromFile()
{
    int length1 = 0;
    int length1Answer = 0;
    int length2 = 0;
    int length2Answer = 6;
    int lengthOfNotFile = 0;
    lengthArrayFromFile("TestFile1.txt", &length1);
    lengthArrayFromFile("TestFile2.txt", &length2);

    return length1 == length1Answer && length2 == length2Answer &&
        lengthArrayFromFile("trap.txt", &lengthOfNotFile) == -1;
}

//bool testLengthArrayFromFile()
//{
//    int length2 = 6;
//    int array2[100] = { 0 };
//    int array2Answer[6] = { 22, 135, 15, 120, 215, 124 };
//    int notFile[1] = { 0 };
//    readArrayFromFile("TestFile2.txt", array2, length2);
//
//    return checkThatAnArraysAreIdentical(array2, array2Answer, 6) &&
//        lengthArrayFromFile("trap.txt", notFile) == -1;
//}

int main()
{
    if (!testLengthArrayFromFile())
    {
        printf("Tests failed.");
        return -1;
    }
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
    if (lengthArrayFromFile("f.txt", &lengthOfF) == -1)
    {
        printf("File g.txt not found!");
        return -1;
    }

    int* arrayF = calloc(lengthOfF, sizeof(int));
    if (arrayF == NULL)
    {
        printf("Not enought memory to create array(");
        return -1;
    }
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
            fprintf(file, "%d ", arrayF[i]);
        }
    }
    fclose(file);
    free(arrayF);
}

