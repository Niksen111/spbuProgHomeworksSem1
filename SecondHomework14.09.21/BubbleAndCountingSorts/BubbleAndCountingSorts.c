#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void swap(int* firstVariable, int* secondVariable)
{
    *firstVariable ^= *secondVariable;
    *secondVariable ^= *firstVariable;
    *firstVariable ^= *secondVariable;
}

void bubbleSort(int theArray[], const int lengthOfArray)
{
    bool changes = true;
    int rightBorder = lengthOfArray;
    while (changes)
    {
        changes = false;
        for (int i = 0; i < rightBorder - 1; ++i)
        {
            if (theArray[i] > theArray[i + 1])
            {
                changes = true;
                swap(&theArray[i], &theArray[i + 1]);
            }
        }
        --rightBorder;
    }
}

int maxElementInArray(const int theArray[], const int lengthOfTheArray)
{
    int maximum = theArray[0];
    for (int i = 1; i < lengthOfTheArray; ++i)
    {
        if (theArray[i] > maximum)
        {
            maximum = theArray[i];
        }
    }
    return maximum;
}

int minElementInArray(const int theArray[], const int lengthOfTheArray)
{
    int minimum = theArray[0];
    for (int i = 1; i < lengthOfTheArray; ++i)
    {
        if (theArray[i] < minimum)
        {
            minimum = theArray[i];
        }
    }
    return minimum;
}

void sortByCounting(int theArray[], const int lengthOfArray)
{
    const int maxElement = maxElementInArray(theArray, lengthOfArray);
    const int minElement = minElementInArray(theArray, lengthOfArray);
    const int rangeOfNumbers = maxElement - minElement + 1;

    int* countingArray = (int*)calloc(rangeOfNumbers, sizeof(int));

    if (countingArray == NULL)
    {
        printf("Sorry, but the array cannot be sorted due to lack of RAM :(\n");
        return;
    }

    for (int i = 0; i < lengthOfArray; ++i)
    {
        ++countingArray[theArray[i] - minElement];
    }

    int indexNow = 0;
    for (int i = 0; i < rangeOfNumbers; ++i)
    {
        for (int j = 0; j < countingArray[i]; ++j)
        {
            theArray[indexNow] = i + minElement;
            ++indexNow;
        }
    }
    free(countingArray);
}

void printArray(const int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%d ", theArray[i]);
    }
}

void scanArray(const int theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        scanf("%d", &theArray[i]);
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

bool testBubbleSort()
{
    int firstArray[5] = { 2, 3, 1, 5, 2 };
    const int sortedTheFirstArray[5] = { 1, 2, 2, 3, 5 };
    bubbleSort(firstArray, 5);

    int secondArray[3] = { -1, -1, -1 };
    const int sortedTheSecondtArray[3] = { -1, -1, -1 };
    bubbleSort(secondArray, 3);

    return (checkThatAnArraysAreIdentical(firstArray, sortedTheFirstArray, 5) &&
        checkThatAnArraysAreIdentical(secondArray, sortedTheSecondtArray, 3));
}

bool testSortByCounting()
{
    int firstArray[5] = { 2, 3, 1, 5, 2 };
    const int sortedTheFirstArray[5] = { 1, 2, 2, 3, 5 };
    sortByCounting(firstArray, 5);

    int secondArray[3] = { -1, -1, -1 };
    const int sortedTheSecondtArray[3] = { -1, -1, -1 };
    sortByCounting(secondArray, 3);

    return (checkThatAnArraysAreIdentical(firstArray, sortedTheFirstArray, 5) &&
        checkThatAnArraysAreIdentical(secondArray, sortedTheSecondtArray, 3));
}

void arrayWithRandomElements(int theArray[], int lengthOfTheArray)
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        theArray[i] = rand() % 10000;
    }
}

int main()
{
    if (!testBubbleSort() || !testSortByCounting())
    {
        printf("Tests failed\n");
        return 0;
    }

    int lengthOfTheUesersArray = 0;

    short int whoWillFillInTheArray = 0;
    printf("Who will fill in the array?\n");
    printf("(Enter 1 if an user, or 0 if a computer)\n");
    scanf("%hd", &whoWillFillInTheArray);

    printf("Enter length of the array:\n");
    scanf("%d", &lengthOfTheUesersArray);

    int* usersArray = (int*)calloc(lengthOfTheUesersArray, sizeof(int));
    int* copyOfTheUsersArray = (int*)calloc(lengthOfTheUesersArray, sizeof(int));

    // Intializes random number generator
    srand((unsigned)time(NULL));

    if (usersArray == NULL || copyOfTheUsersArray == NULL)
    {
        printf("Sorry, but the array cannot be created due to lack of RAM :(\n");
        free(usersArray);
        free(copyOfTheUsersArray);
        return 0;
    }

    if (whoWillFillInTheArray == 1)
    {
        printf("Enter your integer array:\n");
    }

    for (int i = 0; i < lengthOfTheUesersArray; ++i)
    {
        int currentNumber = 0;
        if (whoWillFillInTheArray)
        {
            scanf("%d", &currentNumber);
        }
        else
        {
            currentNumber = rand() % 10000;
        }

        usersArray[i] = currentNumber;
        copyOfTheUsersArray[i] = currentNumber;
    }
    printf("\n");

    const int timeBeforeBubbleSort = clock();
    bubbleSort(usersArray, lengthOfTheUesersArray);
    const int timeAfterBubbleSort = clock();
    sortByCounting(copyOfTheUsersArray, lengthOfTheUesersArray);
    const int timeAfterSortByCounting = clock();

    bool arraysAreIdentical = true;

    for (int i = 0; i < lengthOfTheUesersArray; ++i)
    {
        if (usersArray[i] != copyOfTheUsersArray[i])
        {
            arraysAreIdentical = false;
            break;
        }
    }

    if (!arraysAreIdentical)
    {
        printf("The array after bubble sort and the array after ");
        printf("sort by counting are NOT identical.\n");
        return 0;
    }

    printf("The array after bubble sort and the array after ");
    printf("sort by counting are identical.\n");

    printf("Time before bubble sorting is %d.\n", timeBeforeBubbleSort);
    printf("Time after bubble sorting is %d.\n", timeAfterBubbleSort);
    printf("Time of bubble sorting is %d.\n\n", timeAfterBubbleSort - timeBeforeBubbleSort);

    printf("Time before sorting by counting is %d.\n", timeAfterBubbleSort);
    printf("Time after sorting by counting is %d.\n", timeAfterSortByCounting);
    printf("Time of sorting by counting is %d.\n\n", timeAfterSortByCounting - timeAfterBubbleSort);

    printf("Do you want to print the array?\n");
    printf("(Enter 1 if yes or 0 if no)\n");

    short int willPrint = 0;
    scanf("%hd", &willPrint);

    if (willPrint == 1)
    {
        printArray(usersArray, lengthOfTheUesersArray);
    }
    free(usersArray);
    free(copyOfTheUsersArray);
}