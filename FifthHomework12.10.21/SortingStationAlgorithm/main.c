#include <stdio.h>
#include <stdlib.h>
#include "sortingStationAlgorithm.h"
#include "sortingStationAlgorithmTests.h"
#include "stackTests.h"

int main()
{
    if (!testStack() || !testConvertToPostfixForm())
    {
        printf("Tests failed(\n");
        return -1;
    }
    char expression[1010] = { 0 };
    printf("Enter an expression in infix form (less then 1000 symbols):\n");
    scanf("%[^\n]s", expression);
    int errorCode1 = 0;
    const char* postfix = convertToPostfixForm(expression, &errorCode1);
    printf("%s\n", postfix);

    free(postfix);
    return 0;
}
