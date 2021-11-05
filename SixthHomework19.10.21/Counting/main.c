#include <stdio.h>
#include "circleList.h"
#include "circleListTests.h"

int giveNumberOfSurvivor(CircleList** myList, int numberOfWarriors,
                         int killIndex)
{
    int errorCode1 = 0;
    while (*myList != getNext(*myList, &errorCode1) && errorCode1 == 0)
    {
        int n = killIndex % numberOfWarriors + killIndex *
                (killIndex % numberOfWarriors == 0) - 1;
        switchToN(myList, n);
        int errorCode = 0;
        popNext(myList, &errorCode);
        --numberOfWarriors;
    }
    return getCurrentPositionValue(myList, &errorCode1);
}

bool testGiveNumberOfSurvivor()
{
    CircleList* list1 = createCircleList();
    for (int i = 0; i < 7; ++i)
    {
        push(&list1, i);
    }
    bool result = giveNumberOfSurvivor(&list1, 7, 3) == 3;
    deleteCircleList(&list1);
    for (int i = 0; i < 4; ++i)
    {
        push(&list1, i);
    }
    result = result && giveNumberOfSurvivor(&list1, 4, 5);
    deleteCircleList(&list1);
    return result;
}

int main()
{
    if (!testCircleList() || !testGiveNumberOfSurvivor())
    {
        printf("Tests failed(\n");
        return -1;
    }
    CircleList* myList = createCircleList();
    int numberOfWarriors = 0;
    int killIndex = 0;
    printf("Enter n and m:\n");
    scanf("%d %d", &numberOfWarriors, &killIndex);
    for (int i = 0; i < numberOfWarriors; ++i)
    {
        push(&myList, i);
    }
    int indexOfSurvivor = giveNumberOfSurvivor(&myList, numberOfWarriors, killIndex);
    deleteCircleList(&myList);
    printf("Index of survivor equals %d", indexOfSurvivor);
    return 0;
}
