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

void halfQSort(int theArray[], int lengthOfTheArray)
{
    int supportElement = theArray[0];

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
}

bool checkTheArrayIsHalfQSorted(int theArray[], int lengthOfTheArray, int supportElement)
{
    // This variable checks if the last element was larger of equal to
    // the support element and the next element smaller then the support element.
    // If variable is true, then array is'nt half QSorted.
    bool conditionViolation = false;

    for (int i = 0; i < lengthOfTheArray - 1; ++i)
    {
        if (theArray[i] >= supportElement && theArray[i + 1] < supportElement)
        {
            conditionViolation = true;
            break;
        }
    }

    return !conditionViolation;
}

bool testHalfQSort()
{
    int firstArray[5] = { 2, 3, 1, 5, 2 };
    halfQSort(firstArray, 5);

    int secondArray[3] = { -1, -1, -1 };
    halfQSort(secondArray, 3);

    int thirdArray[1] = { 0 };
    halfQSort(thirdArray, 1);

    return (checkTheArrayIsHalfQSorted(firstArray, 5, 2) &&
        checkTheArrayIsHalfQSorted(secondArray, 3, -1) &&
        checkTheArrayIsHalfQSorted(thirdArray, 1, 0));
}

bool testCheckTheArrayIsHalfQSorted()
{
    int firstArray[8] = { 2, 5, 7, 4, 11, 8, 9, 8 };
    int secondArray[8] = { -5, 11, 35, 9, 44, 6, 0, 111 };
    return (checkTheArrayIsHalfQSorted(firstArray, 8, 8) &&
        checkTheArrayIsHalfQSorted(secondArray, 8, 6) == false);
}

bool testHalfQSortOnRandomArrays(int maxLengthOfTheArrays, int numberOfArrays)
{
    srand((unsigned)time(NULL));

    int* randomArray = (int*)calloc(maxLengthOfTheArrays, 4);
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
        halfQSort(randomArray, lengthOfTheArray);

        if (!checkTheArrayIsHalfQSorted(randomArray, lengthOfTheArray, supportElement))
        {
            sortIsWorking = false;
            break;
        }
    }
    free(randomArray);
    return sortIsWorking;
}

int main()
{
    if (!testHalfQSort() || !testCheckTheArrayIsHalfQSorted())
    {
        printf("Tests failed!\n");
        return 0;
    }

    srand((unsigned)time(NULL));

    // We use arrays of small length for easy visualization.
    int justArray[1010] = { 0 };
    int lengthOfTheJustArray = rand() % 30;
    int mod = 20;

    arrayWithRandomElements(justArray, lengthOfTheJustArray, mod);

    int supportElement = justArray[0];

    printf("The array befor Half QSort:\n");
    printArray(justArray, lengthOfTheJustArray);

    printf("The support element is %d\n\n", supportElement);
    halfQSort(justArray, lengthOfTheJustArray);

    printf("The array after Half QSort:\n");
    printArray(justArray, lengthOfTheJustArray);

    if (checkTheArrayIsHalfQSorted(justArray, lengthOfTheJustArray, supportElement))
    {
        printf("The array is Half QSorted :)");
    }
    else
    {
        printf("The array is'nt Half QSorted :(");
    }
}
