#include "postfixCalculatorTests.h"
#include "postfixCalculator.h"
#include "../Stack/stackTests.h"

bool testCalculation()
{
    char postfixCalculatorEnter1[30] = "4 6 + 5 / 3 * 8 2 - /";
    char postfixCalculatorEnter2[30] = "4 6 + 5 / 3 * 8 2 - / -";
    char postfixCalculatorEnter3[30] = "4 6 - 5 - 3 * 8 2 - /";
    char postfixCalculatorEnter4[30] = "9 6 - 1 2 + * ";
    int errors[4] = { 0 };
    int result1 = postfixCalculator(postfixCalculatorEnter1, &errors[0]);
    int result2 = postfixCalculator(postfixCalculatorEnter2, &errors[1]);
    int result3 = postfixCalculator(postfixCalculatorEnter3, &errors[2]);
    int result4 = postfixCalculator(postfixCalculatorEnter4, &errors[3]);
    return result1 == 1 && errors[0] == 0 &&
           result2 == 0 && errors[1] == -4 &&
           result3 == -3 && errors[2] == 0 &&
           result4 == 9 && errors[3] == 0;
}

bool testPostfixCalculator()
{
    return testCalculation() && testStack();
}