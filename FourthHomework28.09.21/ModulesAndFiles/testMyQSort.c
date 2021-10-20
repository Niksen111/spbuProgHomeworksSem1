#include "testMyQSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "myQSort.h"
#include "WorkWithArrays.h"

bool testMyQSortOnRandomArrays(const int maxLengthOfTheArrays, const int numberOfArrays)
{
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
    return  testMyQSortOnRandomArrays(1000, 1000) &&
    testMyQSortOnStableArrays();
}