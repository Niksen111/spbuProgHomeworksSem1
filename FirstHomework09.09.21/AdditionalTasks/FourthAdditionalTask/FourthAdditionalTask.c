#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main()
{
    printf("Enter an integer number:\n");
    int theNumber = 0;
    scanf("%d", &theNumber);

    printf("All the prime numbers up to the entered number:\n");

    for (int i = 2; i <= theNumber; ++i) {

        bool numberIsPrime = true;

        for (int j = 2; j * j <= i; ++j)
        {
            if (i % j == 0)
            {
                numberIsPrime = false;
                break;
            }
        }

        if (numberIsPrime)
        {
            printf("%d\n", i);
        }
    }

    printf("The end :)");
}
