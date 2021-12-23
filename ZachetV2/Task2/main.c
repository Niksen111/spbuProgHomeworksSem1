#include <stdio.h>
#include "queueTests.h"

int main()
{
    if (!testQueue())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    printf("All ok :)\n");
    return 0;
}
