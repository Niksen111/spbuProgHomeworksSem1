#include "states.h"
#include "statesTests.h"
#include <stdio.h>

int main()
{
    if (!testStates())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    States* states = createStatesFromFile("testFile.txt");
    printStates(states);
    deleteStates(&states);
    return 0;
}
