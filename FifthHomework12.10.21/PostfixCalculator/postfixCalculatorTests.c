#include "postfixCalculatorTests.h"
#include "postfixCalculator.h"
#include "../Stack/stackTests.h"

bool testOperation()
{
    int errors[8] = { 0 };
    int answers[8] = { 0 };
    answers[0] = operation(4, 0, '/', &errors[0]);
    answers[1] = operation(4, 5, '#', &errors[1]);
    answers[2] = operation(-11, 7, '+', &errors[2]);
    answers[3] = operation(4, -5, '-', &errors[3]);
    answers[4] = operation(4, 0, '*', &errors[4]);
    answers[5] = operation(8, -2, '/', &errors[5]);
    answers[6] = operation(4, -5, '*', &errors[6]);
    answers[7] = operation(6, 5, '/', &errors[7]);


    return  answers[0] == 0 && errors[0] == -1 &&
            answers[1] == 0 && errors[1] == -2 &&
            answers[2] == -4 && errors[2] == 0 &&
            answers[3] == 9 && errors[3] == 0 &&
            answers[4] == 0 && errors[4] == 0 &&
            answers[5] == -4 && errors[5] == 0 &&
            answers[6] == -20 && errors[6] == 0 &&
            answers[7] == 1 && errors[7] == 0;
}

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
    return testCalculation() && testOperation() && testStack();
}