#include <stdio.h>
#include "parseTreeTests.h"

int main()
{
    if (!testParseTree())
    {
        printf("Tests failed(\n");
        return -1;
    }
    printf("%d %d %d %d\n", '+', '-', '*', '/');
    return 0;
}
