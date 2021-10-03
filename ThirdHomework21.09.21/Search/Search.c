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

bool testBinarySearch()
{
    int array1[10] = { 0, 1, 1, 2, 3, 3, 4, 5, 6, 7 };
    int array2[15] = { -13, -11, -7, -5, -3, -2, -1, 0, 1, 1, 2, 3, 5, 8 , 13};

    return (binarySearch(array1, 10, 6) && binarySearch(array1, 10, 0)&&
        !binarySearch(array1, 10, 8) && binarySearch(array2, 15, -7) &&
        binarySearch(array2, 15, 13) && !binarySearch(array2, 15, -9));
}

int main()
{
    if (!testBinarySearch())
    {
        printf("Tests failed(\n");
        return 0;
    }

    int n = 0;
    int k = 0;
    printf("Enter two numbers (separated by a space):\n");
    scanf("%d %d", &n, &k);

    int* randomArray = (int*)calloc(n, sizeof(int));
    int* randomElements = (int*)calloc(k, sizeof(int));

    bool ifPrint = false;
    short ifPrintHelp = 0;
    printf("Do you want to print every array? (1 or 0)\n");
    scanf("%hd", &ifPrintHelp);
    ifPrint = (ifPrintHelp ? true : false);
    printf("%d", ifPrint);
}
