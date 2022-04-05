#include <stdio.h>
#include <string.h>

int counterOfZeros(int theArray[], int lengthOfTheArray)
{
    int numberOfZeros = 0;

    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        if (theArray[i] == 0)
        {
            ++numberOfZeros;
        }
    }

    return numberOfZeros;
}

int main()
{
    printf("Enter length of your array (less then 10000):\n");
    int lengthOfTheArray = 0;
    scanf("%d", &lengthOfTheArray);

    printf("Enter an integer array:\n");
    int theArray[10100] = { 0 };

    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        scanf("%d", &theArray[i]);
    }

    int numberOfZeros = counterOfZeros(theArray, lengthOfTheArray);

    printf("This array has %d zeros.", numberOfZeros);
}
