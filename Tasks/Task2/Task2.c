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

void selectionSort(int theArray[], const int lengthOfTheArray)
{
    int minElement = theArray[0];
    int indexOfMinElement = 0;
    int currentIndex = 0;
    bool changes = true;
    while (changes)
    {
        minElement = theArray[currentIndex];
        indexOfMinElement = currentIndex;
        changes = false;
        for (int i = currentIndex + 1; i < lengthOfTheArray; ++i)
        {
            if (theArray[i] < minElement)
            {
                changes = true;
                minElement = theArray[i];
                indexOfMinElement = i;
            }
        }
        swap(&theArray[currentIndex], &theArray[indexOfMinElement]);
        ++currentIndex;
    }
}

int main()
{
    int usersArray[10] = { 0 };
    scanArray(usersArray, 10);

    selectionSort(usersArray, 10);
    printf("\nUser's array after selection sorting:\n\n");
    printArray(usersArray, 10);

}