#include <stdio.h>
#include <stdlib.h>
#include "sortingStationAlgorithm.h"
#include "postfixCalculator.h"
#include "sortingStationAlgorithmTests.h"
#include "advancedBracketBalanceTests.h"
#include "stackTests.h"
#include "postfixCalculatorTests.h"
#include "advancedBracketBalance.h"

int main() {
    if (!testAdvancedBracketBalance() || !testStack() ||
        !testPostfixCalculator() || !testConvertToPostfixForm())
    {
        printf("Tests failed(\n");
        return -1;
    }
    char expression[1010] = { 0 };
    printf("Enter an expression in infix form (less then 1000 symbols):\n");
    scanf("%[^\n]s", expression);
    int errorCode1 = 0;
    int errorCode2 = 0;
    char* postfix = convertToPostfixForm(expression, &errorCode1);
    printf("%s\n", postfix);
    handleTheBracketError(errorCode1);
    printf("%d\n", calculatePostfixExpression(postfix, &errorCode2));
    handleErrorOfPostfixExpression(errorCode2);

    free(postfix);
    return 0;
}
