#include "testMyQSort.h"
#include "myQSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool testInsertionSort()
{
    int firstArray[5] = { 2, 3, 1, 5, 2 };
    const int sortedTheFirstArray[5] = { 1, 2, 2, 3, 5 };
    insertionSort(firstArray, 5);

    int secondArray[3] = { -1, -1, -1 };
    const int sortedTheSecondtArray[3] = { -1, -1, -1 };
    insertionSort(secondArray, 3);

    int thirdArray[10] = { 2, 5, 5, 1, 8, 3, 9, 4, 0, 7 };
    const int sortedTheThirdArray[10] = { 0, 1, 2, 3, 4, 5, 5, 7, 8, 9 };
    insertionSort(thirdArray, 10);

    return checkThatAnArraysAreIdentical(firstArray, sortedTheFirstArray, 5) &&
           checkThatAnArraysAreIdentical(secondArray, sortedTheSecondtArray, 3) &&
           checkThatAnArraysAreIdentical(thirdArray, sortedTheThirdArray, 10);
}

bool testMyQSortOnRandomArrays(const int maxLengthOfTheArrays, const int numberOfArrays)
{
    srand((unsigned)time(NULL));

    int* randomArray = (int*)calloc(maxLengthOfTheArrays, sizeof(int));
    bool sortIsWorking = true;

    if (randomArray == NULL)
    {
        return true;
    }

    for (int i = 0; i < numberOfArrays; ++i)
    {
        int lengthOfTheArray = rand() % maxLengthOfTheArrays;
        fillArrayWithRandomElements(randomArray, lengthOfTheArray, 1000);
        int supportElement = randomArray[0];
        myQSort(randomArray, lengthOfTheArray);

        if (!checkThatArrayIsSorted(randomArray, lengthOfTheArray))
        {
            printf("Wrong myQSort on the array:\n");
            printArray(randomArray, lengthOfTheArray);
            sortIsWorking = false;
            break;
        }
    }
    free(randomArray);
    return sortIsWorking;
}

bool testMyQSortOnStableArrays()
{
    int array1[5] = { 2, 5, 1, 6, -2 };
    int array2[10] = { 3, 1, 1, 7, -2, 6, -2, -6, 20, 10 };
    int array3[20] = { 5, 2, 5, 2, 6, 2, 6, 0, -3, 12,
                       22, -22, 3, 1, 5, -6, 0, 222, 1, -50 };
    myQSort(array1, 5);
    myQSort(array2, 10);
    myQSort(array3, 20);

    return checkThatArrayIsSorted(array1, 5) && checkThatArrayIsSorted(array2, 10) &&
           checkThatArrayIsSorted(array3, 20);
}

bool testMyQSort()
{
    return testInsertionSort() && testMyQSortOnRandomArrays() &&
    testMyQSortOnStableArrays();
}