#include <stdio.h>
#include "postfixCalculator.h"
#include "postfixCalculatorTests.h"

int main()
{
    if (!testPostfixCalculator())
    {
        printf("Tests failed(\n");
        return 0;
    }
    int errorCode = 0;
    printf("Enter the digits and operations with a space:\n");
    char postfixCalculatorEnter[1000] = { 0 };
    scanf("%[^\n]s", postfixCalculatorEnter);
    int result = calculatePostfixExpression(postfixCalculatorEnter, &errorCode);
    handleTheError(errorCode);
    if (errorCode == 0)
    {
        printf("The result of all operations is %d", result);
    }
}
