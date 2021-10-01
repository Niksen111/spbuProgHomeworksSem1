#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void swap(int* firstVariable, int* secondVariable)
{
    *firstVariable ^= *secondVariable;
    *secondVariable ^= *firstVariable;
    *firstVariable ^= *secondVariable;
}

bool checkThatArrayIsSorted(const int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray - 1; ++i)
    {
        if (theArray[i] > theArray[i + 1])
        {
            return false;
        }
    }
    return true;
}

void arrayWithRandomElements(int theArray[], int lengthOfTheArray, int mod)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        theArray[i] = rand() % mod;
    }
}

void printArray(const int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%d ", theArray[i]);
    }
    printf("\n\n");
}

void insertionSort(int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        int j = i;
        while (theArray[j] < theArray[j - 1] && j > 0)
        {
            swap(&theArray[j], &theArray[j - 1]);
            --j;
        }
    }
}

void myQSort(int theArray[], const int lengthOfTheArray)
{
    if (lengthOfTheArray <= 10)
    {
        insertionSort(theArray, lengthOfTheArray);
        return;
    }

    bool elementsIsNotEqual = false;
    int supportElement = 0;
    for (int i = 0; i < lengthOfTheArray - 1; ++i)
    {
        if (theArray[i] != theArray[i + 1])
        {
            supportElement = max(theArray[i], theArray[i + 1]);
            elementsIsNotEqual = true;
            break;
        }
    }

    if (!elementsIsNotEqual)
    {
        return;
    }

    int i = 0;
    int j = lengthOfTheArray - 1;

    while (i < j)
    {
        while (theArray[i] < supportElement && i < j)
        {
            ++i;
        }

        while (theArray[j] >= supportElement && i < j)
        {
            --j;
        }
        if (i != j)
        {
            swap(&theArray[i], &theArray[j]);
        }
    }

    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        if (theArray[i + 1] >= supportElement)
        {
            myQSort(theArray, i + 1);
            myQSort(&theArray[i + 1], lengthOfTheArray - i - 1);
            return;
        }
    }
}

bool checkThatAnArraysAreIdentical(const int firstArray[],
    const int secondArray[], const int lengthOfArrays)
{
    bool identical = true;

    for (int i = 0; i < lengthOfArrays; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            identical = false;
            break;
        }
    }

    return identical;
}

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

    return (checkThatAnArraysAreIdentical(firstArray, sortedTheFirstArray, 5) &&
        checkThatAnArraysAreIdentical(secondArray, sortedTheSecondtArray, 3) &&
        checkThatAnArraysAreIdentical(thirdArray, sortedTheThirdArray, 10));
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
        arrayWithRandomElements(randomArray, lengthOfTheArray, 1000);
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

bool testMyQSort()
{
    int array1[5] = { 2, 5, 1, 6, -2 };
    int array2[10] = { 3, 1, 1, 7, -2, 6, -2, -6, 20, 10 };
    int array3[20] = { 5, 2, 5, 2, 6, 2, 6, 0, -3, 12,
        22, -22, 3, 1, 5, -6, 0, 222, 1, -50 };
    myQSort(array1, 5);
    myQSort(array2, 10);
    myQSort(array3, 20);

    return (checkThatArrayIsSorted(array1, 5) && checkThatArrayIsSorted(array2, 10) &&
        checkThatArrayIsSorted(array3, 20));
}

int main()
{
    if (!testMyQSort() || !testInsertionSort() || !testMyQSortOnRandomArrays(1000, 1000))
    {
        printf("Tests failed(\n");
        return 0;
    }

    srand((unsigned)time(NULL));
    int lengthOfRandomArray = rand() % 20;
    int rangeOfRandomArray = rand() % 30;
    
    int* randomArray = (int*)calloc(lengthOfRandomArray, sizeof(int));
    arrayWithRandomElements(randomArray, lengthOfRandomArray, rangeOfRandomArray);

    printf("Random array before sorting:\n\n");
    printArray(randomArray, lengthOfRandomArray);
    myQSort(randomArray, lengthOfRandomArray);
    printf("Random array after sorting:\n\n");
    printArray(randomArray, lengthOfRandomArray);

    if (checkThatArrayIsSorted(randomArray, lengthOfRandomArray))
    {
        printf("The array is sorted :)\n");
        return 0;
    }
    printf("The array is'nt sorted :(\n");
    return 0;
}
