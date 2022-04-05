#include <stdio.h>

void printIntegerArray(const int sizeOfAnArray, const int anArray[])
{
    for (int i = 0; i < sizeOfAnArray; ++i)
    {
        printf("%d ", anArray[i]);
    }
}

void swap(int* firstVariable, int* secondVariable)
{
    *firstVariable ^= *secondVariable;
    *secondVariable ^= *firstVariable;
    *firstVariable ^= *secondVariable;
}

void reverseArray(int anArray[], int start, int end)
{
    while (start < end)
    {
        swap(&anArray[start], &anArray[end]);
        ++start;
        --end;
    }
}

int main()
{
    int sizeOfTheFirstArray = 0;
    int sizeOfTheSecondArray = 0;

    printf("Enter sizes of the first array:\n");
    scanf("%d", &sizeOfTheFirstArray);

    printf("Enter sizes of the second array:\n");
    scanf("%d", &sizeOfTheSecondArray);

    int theArray[10100] = { 0 };
    printf("Enter your array:\n");

    for (int i = 0; i < sizeOfTheFirstArray + sizeOfTheSecondArray; ++i)
    {
        scanf("%d", &theArray[i]);
    }

    reverseArray(theArray, 0, sizeOfTheFirstArray - 1);
    reverseArray(theArray, sizeOfTheFirstArray, sizeOfTheFirstArray + sizeOfTheSecondArray - 1);
    reverseArray(theArray, 0, sizeOfTheFirstArray + sizeOfTheSecondArray - 1);

    printf("The array now looks like this:\n");
    printIntegerArray(sizeOfTheFirstArray + sizeOfTheSecondArray, theArray);
}
