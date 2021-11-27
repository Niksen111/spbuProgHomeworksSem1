#include <stdio.h>
#include "mergeSortingTests.h"
#include "listTests.h"

int main()
{
    if (!testMergeSorting() || !testList())
    {
        printf("Tests failed(\n");
        return -1;
    }
    printf("Ok\n");
    return 0;
}
