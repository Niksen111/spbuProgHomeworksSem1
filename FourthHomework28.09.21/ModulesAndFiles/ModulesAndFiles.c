#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "myQSort.h"
#include "testMyQSort.h"
#include "WorkWithArrays.h"

int findTrend(int theArray[], int lengthOfTheArray)
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

int* readArrayFromFile(char nameOfFile[], int* lengthOfTheArray, int* errorNumber) {
    FILE *file = fopen(nameOfFile, "r");
    if (file == NULL)
    {
        *errorNumber = -1;
        return NULL;
    }

    *lengthOfTheArray = 0;
    int temporary = 0;
    while (fscanf(file, "%d", &temporary) != EOF)
    {
        ++*lengthOfTheArray;
    }
    fclose(file);
    FILE* file1 = fopen(nameOfFile, "r");

    int* theArray = calloc(*lengthOfTheArray, sizeof(int));
    
    if (theArray == NULL)
    {
        fclose(file1);
        *errorNumber = -2;
        return NULL;
    }

    for (int i = 0; i < *lengthOfTheArray; ++i)
    {
        fscanf(file1, "%d ", &theArray[i]);
    }

    fclose(file1);
    *errorNumber = 0;
    return theArray;
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
    int lengthOfTheArray = 0;
    int errorNumber = 0;
    int* arrayReading = readArrayFromFile("testFile1.txt", &lengthOfTheArray, &errorNumber);
    
    if (errorNumber != 0)
    {
        return false;
    }

    return lengthOfTheArray == 10 && checkThatAnArraysAreIdentical(arrayAnswer, arrayReading, 10);
}

bool testFindTrend()
{
    int array1[10] = { 0, 1, 2, 3, 5, 5, 5, 6, 9, 9 };
    int array2[3] = { -10, 0, 10 };

    return findTrend(array1, 10) == 5 && findTrend(array2, 3) == -10;
}

int main()
{
    srand((unsigned)time(NULL));
    if (!testMyQSort() || !testFindTrend() || !testReadFromFile())
    {
        printf("Tests failed(\n");
        return -1;
    }

    printf("We sort the array using QSort and look for a trend over a line.\n( O(n logn) )\n\n");

    char nameOfTheFile[20] = "input.txt";
    int errorNumber = 0;
    int lengthOfTheArray = 0;
    int* justArray = readArrayFromFile(nameOfTheFile, &lengthOfTheArray, &errorNumber);
    if (errorNumber != 0)
    {
        printf("%s\n", errorNumber == -1 ? "File not found!" : 
            "Failed to allocate memory to an array(");
        return -1;
    }

    printf("The array before sorting:\n\n");
    printArray(justArray, 20);

    myQSort(justArray, 20);
    printf("The array after sorting:\n\n");
    printArray(justArray, 20);

    printf("Trend is %d.\n", findTrend(justArray, 20));
}
