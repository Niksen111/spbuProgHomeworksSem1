#include <stdio.h>
#include "searchTreeTests.h"

int main() {
    if (!testSearchTree())
    {
        printf("Tests failed(\n");
        return -1;
    }
    printf("Hello, World!\n");
    return 0;
}
