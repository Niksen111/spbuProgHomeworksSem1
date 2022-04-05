#include <stdio.h>
#include "mergeSortingTests.h"
#include "listTests.h"

int main()
{
    if (!testList() || !testMergeSorting())
    {
        printf("Tests failed(\n");
        return -1;
    }
    printf("Ok\n");
    return 0;
}
