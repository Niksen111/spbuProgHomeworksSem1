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

void insertionSort(int theArray[], int lengthOfTheArray)
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

bool binarySearch(const int theArray[], const int lengthOfTheArray, const int theElement)
{
    int leftBorder = 0;
    int rightBorder = lengthOfTheArray;
    while (rightBorder - leftBorder > 1)
    {
        int middleElement = (leftBorder + rightBorder) / 2;
        if (theElement >= theArray[middleElement])
        {
            leftBorder = middleElement;
        }
        else
        {
            rightBorder = middleElement;
        }
    }
    if (theArray[leftBorder] == theElement)
    {
        return true;
    }
    return false;
}

int main()
{
    srand((unsigned)time(NULL));
    int justArray[20] = { 0 };
    arrayWithRandomElements(justArray, 20, 25);
    printArray(justArray, 20);
    myQSort(justArray, 20);
    printArray(justArray, 20);
    int elem = rand() % 25;
    printf("%d\n", elem);
    if (binarySearch(justArray, 20, elem))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
}
