#include <stdio.h>
#include "sortingStationAlgorithm.h"
#include "postfixCalculator.h"

int main() {
    char expression[100] = "1 + 2 * 3 + 4 * (5 + 6 * 7)";
    int errorCode1 = 0;
    int errorCode2 = 0;
    char* postfix = convertToPostfixForm(expression, &errorCode1);
    printf("%d\n", errorCode1);
    printf("%s\n", postfix);
    printf("%d %d", calculatePostfixExpression(postfix, &errorCode2), errorCode2);

    return 0;
}
