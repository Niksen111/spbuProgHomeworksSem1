#include <stdio.h>
#include <string.h>

int main()
{
    printf("Enter the first and second variables:\n");
    int firstVariable = 0;
    int secondVariable = 0;
    scanf("%d %d", &firstVariable, &secondVariable);

    firstVariable ^= secondVariable;
    secondVariable ^= firstVariable;
    firstVariable ^= secondVariable;

    printf("The first variable now equals %d.\n", firstVariable);
    printf("The second variable now equals %d.", secondVariable);
}
