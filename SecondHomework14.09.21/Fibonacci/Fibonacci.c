#include <stdio.h>
#include <stdbool.h>

unsigned long long fibonacciRecursion(const int number)
{
    if (number == 2 || number == 1)
    {
        return 1;
    }

    if (number < 1 || number > 93)
    {
        return 0;
    }

    return fibonacciRecursion(number - 1) + fibonacciRecursion(number - 2);
}

unsigned long long fibonacciIteraitive(const int number)
{
    if (number == 2 || number == 1)
    {
        return 1;
    }

    if (number < 1 || number > 93)
    {
        return 0;
    }

    unsigned long long penultimateNumber = 1;
    unsigned long long lastNumber = 1;
    unsigned long long currentNumber = 2;

    for (int i = 4; i <= number; ++i)
    {
        penultimateNumber = lastNumber;
        lastNumber = currentNumber;
        currentNumber = penultimateNumber + lastNumber;
    }

    return currentNumber;
}

// All answers were taken from this website 
//https://keisan.casio.com/exec/system/1180573404
bool testRecursion()
{
    return (fibonacciRecursion(1) == 1 && fibonacciRecursion(2) == 1 &&
        fibonacciRecursion(3) == 2 && fibonacciRecursion(10) == 55 &&
        fibonacciRecursion(30) == 832040 && fibonacciRecursion(-5) == 0);
}

bool testIterative()
{
    return (fibonacciIteraitive(1) == 1 && fibonacciIteraitive(2) == 1 &&
        fibonacciIteraitive(3) == 2 && fibonacciIteraitive(10) == 55 &&
        fibonacciIteraitive(93) == 12200160415121876738 && fibonacciIteraitive(-5) == 0);
}

int main()
{
    if (!testRecursion() || !testIterative())
    {
        printf("Tests failed\n");
        return 0;
    }

    int number = 0;
    printf("Enter your number (from 1 to 93):\n");
    scanf("%d", &number);

    if (number < 1 || number > 93)
    {
        printf("Wrong number.\n");
        return 0;
    }

    short int problemsWithScanfBoolVariable = 0;
    printf("If a number greater than 36 is entered,\n");
    printf("the Recursion algorithm starts to run slowly.\n");
    printf("Choose the algorithm, that will decide the task:\n");
    printf("(0 is iteration algorithm, 1 is recurcive algorithm)\n");
    scanf("%hd", &problemsWithScanfBoolVariable);


    if (problemsWithScanfBoolVariable)
    {
        printf("The %d Fibonacci number is %llu", number, fibonacciRecursion(number));
    }
    else
    {
        printf("The %d Fibonacci number is %llu", number, fibonacciIteraitive(number));
    }
}