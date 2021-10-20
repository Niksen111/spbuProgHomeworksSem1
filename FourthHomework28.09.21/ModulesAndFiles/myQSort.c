#include "myQSort.h"
#include <stdbool.h>
#include "WorkWithArrays.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

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

    bool elementsAreNotEqual = false;
    int supportElement = 0;
    for (int i = 0; i < lengthOfTheArray - 1; ++i)
    {
        if (theArray[i] != theArray[i + 1])
        {
            supportElement = MAX(theArray[i], theArray[i + 1]);
            elementsAreNotEqual = true;
            break;
        }
    }

    if (!elementsAreNotEqual)
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