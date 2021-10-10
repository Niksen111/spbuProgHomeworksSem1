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

void convertDecimalToBinaryRepresentation(int decimal, int binaryRepres[])
{
    for (int i = 8 * sizeof(int) - 1; i >= 0; --i)
    {
        binaryRepres[i] = decimal & 1;
        decimal = decimal >> 1;
    }
}

void convertBinaryToDecimalRepresentation(int binaryRepres[], int* decimal)
{
    *decimal = 0;
    for (int i = 0; i < 8 * sizeof(int); ++i)
    {
        *decimal = *decimal << 1;
        *decimal += binaryRepres[i];
    }
}

void sumOfTwoBinaryNumbers(int binNumber1[], int binNumber2[], int answer[])
{
    int sizeOfInt = sizeof(int);
    int *auxiliaryArray = (int*)calloc(sizeOfInt * 8, sizeOfInt);
    for (int i = sizeOfInt * 8 - 1; i >= 0; --i)
    {
        answer[i] = (binNumber1[i] + binNumber2[i] + (i < sizeOfInt * 8 - 1 ? auxiliaryArray[i + 1] : 0)) % 2;
        auxiliaryArray[i] = (int) ((binNumber1[i] + binNumber2[i] + (i < sizeOfInt * 8 - 1 ? auxiliaryArray[i + 1] : 0)) >= 2);
    }
    free(auxiliaryArray);
}

int main()
{
    int number1 = 0;
    int number2 = 0;
    int sizeOfInt = sizeof(int);
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

    int sumOfNumbersDecimal = 0;
    convertBinaryToDecimalRepresentation(sumOfNumbers, &sumOfNumbersDecimal);
    printf("Decimal sum of the numbers %d", sumOfNumbersDecimal);
    free(binNumber1);
    free(binNumber2);
    free(sumOfNumbers);
}