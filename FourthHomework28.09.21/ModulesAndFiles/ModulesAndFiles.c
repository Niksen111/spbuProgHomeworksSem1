#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myQSort.h"
#include "testMyQSort.h"
#include "WorkWithArrays.h"

int findTrend(const int theArray[], int lengthOfTheArray)
{
    int maxTrend = 1;
    int trend = theArray[0];
    int nowLength = 1;
    for (int i = 1; i < lengthOfTheArray; ++i)
    {
        if (theArray[i] == theArray[i - 1])
        {
            ++nowLength;
            if (nowLength > maxTrend)
            {
                maxTrend = nowLength;
                trend = theArray[i];
            }
        }
        else
        {
            nowLength = 1;
        }
    }
    return trend;
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

bool testReadFromFile()
{
    FILE* file = fopen("testFile1.txt", "w");
    int arrayAnswer[10] = { 8, 2, 1, 5, -2, 0, 100, -10000, 8, -5 };
    for (int i = 0; i < 10; ++i)
    {
        fprintf(file, "%d ", arrayAnswer[i]);
    }
    fclose(file);
    int lengthOfTheArray = 10;
    int* arrayReading = calloc(lengthOfTheArray, sizeof(int));

    if (readArrayFromFile("testFile1.txt", arrayReading, lengthOfTheArray) != 0)
    {
        free(arrayReading);
        return false;
    }
    bool testResult = lengthOfTheArray == 10 && checkThatAnArraysAreIdentical(arrayAnswer, arrayReading, 10);
    free(arrayReading);
    return testResult;
}

bool testFindTrend()
{
    int array1[10] = { 0, 1, 2, 3, 5, 5, 5, 6, 9, 9 };
    int array2[3] = { -10, 0, 10 };

    return findTrend(array1, 10) == 5 && findTrend(array2, 3) == -10;
}

int main()
{
    if (!testMyQSort() || !testFindTrend() || !testReadFromFile())
    {
        printf("Tests failed(\n");
        return -1;
    }

    printf("We sort the array using QSort and look for a trend over a line.\n( O(n logn) )\n\n");

    char nameOfTheFile[20] = "input.txt";
    int lengthOfTheArray = 0;
    if (lengthArrayFromFile(nameOfTheFile,&lengthOfTheArray) == -1)
    {
        printf("File not found!");
        return -1;
    }

    int* justArray = calloc(lengthOfTheArray, sizeof(int));

    if (readArrayFromFile(nameOfTheFile, justArray, lengthOfTheArray) == -1)
    {
        free(justArray);
        printf("File not found!");
        return -1;
    }

    printf("The array before sorting:\n\n");
    printArray(justArray, lengthOfTheArray);

    myQSort(justArray, lengthOfTheArray);
    printf("The array after sorting:\n\n");
    printArray(justArray, lengthOfTheArray);

    printf("Trend is %d.\n", findTrend(justArray, lengthOfTheArray));
    free(justArray);
}
