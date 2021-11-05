#include "sortingStationAlgorithmTests.h"
#include "sortingStationAlgorithm.h"
#include <stdlib.h>

bool checkThatAnArraysAreIdentical(const char firstArray[],
                                   const char secondArray[])
{
    for (int i = 0; firstArray[i] != '\0' || secondArray[i] != '\0'; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
}

bool testConvertToPostfixForm()
{
    char expression1[100] = "1 + 2 * 3 + 4 * (5 + 6 * 7)";
    int errorCode1 = 0;
    char answer1[100] = "1 2 3 * + 4 5 6 7 * + * + ";
    char expression2[100] = "(1) + (1) * (2)";
    int errorCode2 = 0;
    char answer2[100] = "1 1 2 * + ";
    char* resultOfConverting1 = convertToPostfixForm(expression1, &errorCode1);
    char* resultOfConverting2 = convertToPostfixForm(expression2, &errorCode2);
    bool resultOfTheTest =
            checkThatAnArraysAreIdentical(resultOfConverting1, answer1) &&
            checkThatAnArraysAreIdentical(resultOfConverting2, answer2) &&
            errorCode1 == 0 && errorCode2 == 0;
    free(resultOfConverting1);
    free(resultOfConverting2);

    return resultOfTheTest;
}
