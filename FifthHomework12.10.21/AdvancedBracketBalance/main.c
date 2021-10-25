#include <stdio.h>
#include "advancedBracketBalance.h"
#include "advancedBracketBalanceTests.h"

int main()
{
    if (!testAdvancedBracketBalance())
    {
        printf("Tests failed.\n");
        return -1;
    }

    char list[1000] = { 0 };
    printf("Enter string (less then 1000 symbols):\n");
    scanf("%[^\n]s", list);
    int errorCode = 0;
    if (areBracketsBalanced(list, &errorCode))
    {
        printf("All ok :)\n");
        return 0;
    }
    handleTheError(errorCode);
    return -1;
}
