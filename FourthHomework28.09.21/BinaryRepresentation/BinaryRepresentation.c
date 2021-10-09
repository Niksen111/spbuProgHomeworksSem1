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
    for (int i = 31; i >= 0; --i)
    {
        binaryRepres[i] = (decimal & 1 ? 1 : 0);
        decimal = decimal >> 1;
    }
    //for (int i = 31; i >= 0; --i)
    //{
    //    binaryRepres[i] = abs(binaryRepres[i] - 1);
    //    if (binaryRepres[i] == 1)
    //    {
    //        return;
    //    }
    //}
}

void convertBinaryToDecimalRepresentation(int binaryRepres[], int* decimal)
{
    *decimal = 0;
    for (int i = 0; i <32; ++i)
    {
        *decimal = *decimal << 1;
        *decimal += binaryRepres[i];
    }
}

int main()
{
    int number1 = 0;
    int number2 = 0;
    printf("Enter two numbers:\n");
    scanf("%d %d", &number1, &number2);

    int binNumber1[32] = { 0 };
    convertDecimalToBinaryRepresentation(number1, binNumber1);

    printArray(binNumber1, 32);

    convertBinaryToDecimalRepresentation(binNumber1, &number2);

    printf("%d", number2);
}