#include <stdio.h>
#include "circleList.h"
#include "circleListTests.h"

int giveNumberOfSurvivor(int numberOfWarriors, int killIndex)
{
    CircleListRoot* myList = createCircleList();
    for (int i = 0; i < numberOfWarriors; ++i)
    {
        push(&myList, i);
    }
    int errorCode1 = 0;
    while (myList != getNext(myList, &errorCode1) && errorCode1 == 0)
    {
        int n = killIndex % numberOfWarriors - 1;
        if (n < 0)
        {
            n += killIndex;
        }
        moveNPositionsForward(&myList, n);
        int errorCode = 0;
        popNext(&myList, &errorCode);
        --numberOfWarriors;
    }
    int indexOfSurvivor = getCurrentPositionValue(myList, &errorCode1);
    deleteCircleList(&myList);
    return indexOfSurvivor;
}

bool testGiveNumberOfSurvivor()
{
    bool result = giveNumberOfSurvivor(7, 3) == 3;
    result = result && giveNumberOfSurvivor(4, 5);
    return result;
}

int main()
{
    if (!testCircleList() || !testGiveNumberOfSurvivor())
    {
        printf("Tests failed(\n");
        return -1;
    }
    int numberOfWarriors = 0;
    int killIndex = 0;
    printf("Enter n and m:\n");
    scanf("%d %d", &numberOfWarriors, &killIndex);
    const int indexOfSurvivor = giveNumberOfSurvivor(numberOfWarriors, killIndex);
    printf("Index of survivor equals %d", indexOfSurvivor);
    return 0;
}
