#include <stdio.h>
#include "circleList.h"
#include <stdlib.h>

int giveNumberOfSurvivor(CircleList** myList, int numberOfWarriors,
                         int killIndex)
{
    while (*myList != (*myList)->next)
    {
        switchToN(myList, killIndex % numberOfWarriors - 1);
        int errorCode = 0;
        popNext(myList, &errorCode);
        --numberOfWarriors;
    }
    return ((*myList)->value);
}

int main() {
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
    //deleteCircleList(&myList);
    myList->next = NULL;
    free(*&myList);
    printf("Index of survivor equals %d", indexOfSurvivor);
    return 0;
}
