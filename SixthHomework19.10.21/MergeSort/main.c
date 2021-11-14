#include <stdio.h>
#include "mergeSortingTests.h"

int main()
{
    if (!testMergeSorting())
    {
        printf("Tests failed(\n");
        return -1;
    }
    printf("Hello, World!\n");
    return 0;
}
