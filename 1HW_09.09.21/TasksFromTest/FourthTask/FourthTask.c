#include <stdio.h>
#include <string.h>

int main()
{
    printf("%s", "Enter your number: ");
    int theNumber = 0;
    scanf_s("%d", &theNumber);

    long int squareOfTheNumber = theNumber * theNumber;
    long int result = (squareOfTheNumber + 1) * (squareOfTheNumber + theNumber) + 1;

    printf("%s %d\n", "The result is", result);

    printf("%s\n", "Press \"Enter\" to exit");
}
