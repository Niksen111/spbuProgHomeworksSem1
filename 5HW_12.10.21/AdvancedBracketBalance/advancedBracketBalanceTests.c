#include "advancedBracketBalanceTests.h"
#include "../Stack/stackTests.h"
#include "advancedBracketBalance.h"

bool testAreBracketsBalanced()
{
    char list1[30] = "()[]{}([{([{}])}])([]{})";
    char list2[30] = "";
    char list3[30] = "([{()})]";
    int errors[3] = { 0 };

    return areBracketsBalanced(list1, &errors[0]) &&
        areBracketsBalanced(list2, &errors[1]) &&
        !areBracketsBalanced(list3, &errors[2]) &&
        errors[0] == 0 && errors[1] == 0 && errors[2] == -2;
}

bool testAdvancedBracketBalance()
{
    return testAreBracketsBalanced() && testStack();
}