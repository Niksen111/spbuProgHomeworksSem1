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

void fillArrayWithRandomElements(int theArray[], int lengthOfTheArray, int mod)
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

    bool elementsAreNotEqual  = false;
    int supportElement = 0;
    for (int i = 0; i < lengthOfTheArray - 1; ++i)
    {
        if (theArray[i] != theArray[i + 1])
        {
            supportElement = max(theArray[i], theArray[i + 1]);
            elementsAreNotEqual  = true;
            break;
        }
    }

    if (!elementsAreNotEqual )
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

    myQSort(theArray, i);
    myQSort(&theArray[i], lengthOfTheArray - i);
}

bool binarySearch(const int theArray[], const int lengthOfTheArray, const int theElement)
{
    int leftBorder = 0;
    int rightBorder = lengthOfTheArray;
    while (rightBorder - leftBorder > 1)
    {
        const int middleElement = (leftBorder + rightBorder) / 2;
        if (theElement >= theArray[middleElement])
        {
            leftBorder = middleElement;
        }
        else
        {
            rightBorder = middleElement;
        }
    }
    return theArray[leftBorder] == theElement ? true : false;
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

bool testBinarySearch()
{
    int array1[10] = { 0, 1, 1, 2, 3, 3, 4, 5, 6, 7 };
    int array2[15] = { -13, -11, -7, -5, -3, -2, -1, 0, 1, 1, 2, 3, 5, 8, 13};

    return binarySearch(array1, 10, 6) && binarySearch(array1, 10, 0) &&
        !binarySearch(array1, 10, 8) && binarySearch(array2, 15, -7) &&
        binarySearch(array2, 15, 13) && !binarySearch(array2, 15, -9);
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

bool testMyQSort()
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

int main()
{
    if (!testBinarySearch() || !testInsertionSort() || !testMyQSort() || !testMyQSortOnRandomArrays(1000, 1000))
    {
        printf("Tests failed(\n");
        return -1;
    }

    int n = 0;
    int k = 0;
    printf("Enter two numbers (separated by a space):\n");
    scanf("%d %d", &n, &k);

    int* randomArray = (int*)calloc(n, sizeof(int));
    int* randomElements = (int*)calloc(k, sizeof(int));

    fillArrayWithRandomElements(randomArray, n, n);
    fillArrayWithRandomElements(randomElements, k, n + 1);
    
    printf("The array befor sorting:\n\n");
    printArray(randomArray, n);
    myQSort(randomArray, n);
    printf("The array after sorting:\n\n");
    printArray(randomArray, n);

    for (int i = 0; i < k; ++i)
    {
        if (binarySearch(randomArray, n, randomElements[i]))
        {
            printf("Element %d is contained in the array.\n", randomElements[i]);
        }
        else
        {
            printf("Element %d is not contained in the array.\n", randomElements[i]);
        }
    }
    free(randomArray);
    free(randomElements);
}
