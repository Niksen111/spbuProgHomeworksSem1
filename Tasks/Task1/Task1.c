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
    printf("\n\n");
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

void fillArrayWithRandomElements(int theArray[], int lengthOfTheArray, int mod)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        theArray[i] = rand() % mod;
    }
}

int sumOfDigits(int number)
{
    int sum = 0;
    while (number != 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

void findNumberWithMaxSumOfDigits(int theArray[], int lengthOfTheArray, int replyArray[], int *lengthOfReplyArray)
{
    int maxSum = 0;
    int* arrayWithSums = (int*)calloc(lengthOfTheArray, sizeof(int));
    
    if (arrayWithSums == NULL)
    {
        printf("Sorry, but the array cannot be sorted due to lack of RAM :(\n");
        return;
    }

    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        int localSum = sumOfDigits(theArray[i]);
        arrayWithSums[i] = localSum;
        if (localSum > maxSum)
        {
            maxSum = localSum;
        }
    }

    *lengthOfReplyArray = 0;
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        if (arrayWithSums[i] == maxSum)
        {
            replyArray[*lengthOfReplyArray] = theArray[i];
            ++*lengthOfReplyArray;
        }
    }

}

bool testFindNumberWithMaxSumOfDigits()
{
    int array1[3] = { 111, 234, 55 };
    int answerForArray1[3] = { 0 };
    int lengthOfAnswersNumber = 0;
    int rigthAnswer[1] = { 55 };
    findNumberWithMaxSumOfDigits(array1, 3, answerForArray1, &lengthOfAnswersNumber);
    bool ans = checkThatAnArraysAreIdentical(answerForArray1, rigthAnswer, max(1, lengthOfAnswersNumber));

    return(ans);
}

int main()
{
    if (!testFindNumberWithMaxSumOfDigits())
    {
        printf("Tests failed(");
        return 0;
    }
    int randomArray[15] = { 0 };
    fillArrayWithRandomElements(randomArray, 15, 10000);
    int arrayWithOurNumbers[15] = { 0 };
    int lengthOfReplyArray = 0;

    printf("Random array:\n\n");
    printArray(randomArray, 15);

    findNumberWithMaxSumOfDigits(randomArray, 15, arrayWithOurNumbers, &lengthOfReplyArray);

    printf("Numbers with a maximum sum of digits:\n");
    for (int i = 0; i < lengthOfReplyArray; ++i)
    {
        printf("%d ", arrayWithOurNumbers[i]);
    }
}