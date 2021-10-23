#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
    for (int i = 0; i < lengthOfArrays; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
}

void convertDecimalToBinaryRepresentation(int decimal, int binaryRepresentation[])
{
    for (int i = 8 * sizeof(int) - 1; i >= 0; --i)
    {
        binaryRepresentation[i] = decimal & 1;
        decimal = decimal >> 1;
    }
}

int convertBinaryToDecimalRepresentation(int binaryRepresentation[])
{
    int decimal = 0;
    for (int i = 0; i < 8 * sizeof(int); ++i)
    {
        decimal = decimal << 1;
        decimal += binaryRepresentation[i];
    }
    return decimal;
}

void sumOfTwoBinaryNumbers(int binNumber1[], int binNumber2[], int answer[])
{
    const int sizeOfInt = sizeof(int);
    int transferableBit = 0;
    for (int i = sizeOfInt * 8 - 1; i >= 0; --i)
    {
        answer[i] = (binNumber1[i] + binNumber2[i] + transferableBit) % 2;
        transferableBit = (int) ((binNumber1[i] + binNumber2[i] + transferableBit) >= 2);
    }
}

bool testConvertBinaryToDecimalRepresentation()
{
    int number1Answer = 1024;
    int number1Binary[32] = { 0 };
    number1Binary[21] = 1;
    int number1 = convertBinaryToDecimalRepresentation(number1Binary);
    int number2Answer = -35;
    int number2Binary[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
    int number2 = convertBinaryToDecimalRepresentation(number2Binary);
    int number3Answer = 0;
    int number3Binary[32] = { 0 };
    int number3 = convertBinaryToDecimalRepresentation(number3Binary);

    return number1 == number1Answer && number2 == number2Answer &&
        number3 == number3Answer;
}

bool testConvertDecimalToBinaryRepresentation()
{
    int number1 = 1024;
    int number1Binary[32] = { 0 };
    convertDecimalToBinaryRepresentation(number1, number1Binary);
    int number1BinaryAnswer[32] = { 0 };
    number1BinaryAnswer[21] = 1;
    int number2 = -35;
    int number2Binary[32] = { 0 };
    convertDecimalToBinaryRepresentation(number2, number2Binary);
    int number2BinaryAnswer[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
    int number3 = 0;
    int number3Binary[32] = { 0 };
    convertDecimalToBinaryRepresentation(number3, number3Binary);
    int number3BinaryAnswer[32] = { 0 };

    return checkThatAnArraysAreIdentical(number1BinaryAnswer, number1Binary, 32) && 
        checkThatAnArraysAreIdentical(number2BinaryAnswer, number2Binary, 32) &&
        checkThatAnArraysAreIdentical(number3BinaryAnswer, number3Binary, 32);

}

bool testSumOfTwoBinaryNumbers()
{
    int number1Binary[32] = { 0 };
    number1Binary[21] = 1;
    int number2Binary[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
    int number3Binary[32] = { 0 };
    int sumOf1and2Numbers[32] = { 0 };
    int sumOf1and2NumbersAnswer[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
    int sumOf2and3Numbers[32] = { 0 };
    int sumOf2and3NumbersAnswer[32] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1 };
    int sumOf1and3Numbers[32] = { 0 };
    int sumOf1and3NumbersAnswer[32] = { 0 };
    sumOf1and3NumbersAnswer[21] = 1;
    sumOfTwoBinaryNumbers(number1Binary, number2Binary, sumOf1and2Numbers);
    sumOfTwoBinaryNumbers(number2Binary, number3Binary, sumOf2and3Numbers);
    sumOfTwoBinaryNumbers(number1Binary, number3Binary, sumOf1and3Numbers);

    return checkThatAnArraysAreIdentical(sumOf1and2Numbers, sumOf1and2NumbersAnswer, 32) &&
        checkThatAnArraysAreIdentical(sumOf2and3Numbers, sumOf2and3NumbersAnswer, 32) &&
        checkThatAnArraysAreIdentical(sumOf1and3Numbers, sumOf1and3NumbersAnswer, 32);
}

int main()
{
    if (!testConvertBinaryToDecimalRepresentation() || !testConvertDecimalToBinaryRepresentation() || !testSumOfTwoBinaryNumbers())
    {
        printf("Test failed(\n");
        return -1;
    }
    int number1 = 0;
    int number2 = 0;
    const int sizeOfInt = sizeof(int);
    printf("Enter two numbers:\n");
    scanf("%d %d", &number1, &number2);

    int *binNumber1 = (int*)calloc(8 * sizeOfInt, sizeOfInt);
    int *binNumber2 = (int*)calloc(8 * sizeOfInt, sizeOfInt);
    convertDecimalToBinaryRepresentation(number1, binNumber1);
    convertDecimalToBinaryRepresentation(number2, binNumber2);

    printf("Fitst number:\n");
    printArray(binNumber1, 8 * sizeOfInt);
    printf("Second number:\n");
    printArray(binNumber2, 8 * sizeOfInt);

    int *sumOfNumbers = (int*)calloc(8 * sizeOfInt, sizeOfInt);
    sumOfTwoBinaryNumbers(binNumber1, binNumber2, sumOfNumbers);

    printf("Sum of the numbers:\n");
    printArray(sumOfNumbers, 8 * sizeOfInt);

    int sumOfNumbersDecimal = convertBinaryToDecimalRepresentation(sumOfNumbers);
    printf("Decimal sum of the numbers %d", sumOfNumbersDecimal);
    free(binNumber1);
    free(binNumber2);
    free(sumOfNumbers);
}