#include <stdio.h>
#include <stdbool.h>

long double exponentiation(long double number, int degree)
{
    long double newNumber = 1.;
    if (degree < 0)
    {
        number = 1 / number;
        degree = -degree;
    }

    for (int i = 0; i < degree; ++i)
    {
        newNumber *= number;
    }
    return newNumber;
}

long double binaryExponentiation(long double number, int degree)
{
    if (number == 0.)
    {
        return 0.;
    }

    if (degree < 0)
    {
        number = 1 / number;
        degree = -degree;
    }

    long double newNumber = 1.;

    while (degree > 0)
    {
        if (degree % 2)
        {
            newNumber *= number;
        }
        degree /= 2;
        number *= number;
    }

    return newNumber;
}

bool testExponentiation()
{
    return (exponentiation(2., 0) == 1. && exponentiation(2., 1) == 2. &&
        exponentiation(2., 10) == 1024. && exponentiation(2., 30) == 1073741824. &&
        exponentiation(-2., 5) == -32. && exponentiation(-2., 10) == 1024. &&
        exponentiation(0., 10) == 0. && exponentiation(-2., -10) == 0.0009765625 &&
        exponentiation(2., -3) == 0.125);
}

bool testBinaryExponentiation()
{
    return (binaryExponentiation(2., 0) == 1. && binaryExponentiation(2., 1) == 2. &&
        binaryExponentiation(2., 10) == 1024. && binaryExponentiation(2., 30) == 1073741824. &&
        binaryExponentiation(-2., 5) == -32. && binaryExponentiation(-2., 10) == 1024. &&
        binaryExponentiation(0., 10) == 0. && binaryExponentiation(-2., -10) == 0.0009765625 &&
        binaryExponentiation(2., -3) == 0.125);
}


int main()
{
    if (!testExponentiation() || !testBinaryExponentiation())
    {
        printf("Tests failed\n");
        return 0;
    }

    long double number = 0;
    int degree = 0;

    printf("Enter a number:\n");
    scanf("%Lf", &number);

    printf("Enter a degree:\n");
    scanf("%d", &degree);

    printf("%.20Lf %.20Lf", exponentiation(number, degree), binaryExponentiation(number, degree));
}