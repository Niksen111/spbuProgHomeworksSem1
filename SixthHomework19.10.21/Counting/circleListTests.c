#include "circleListTests.h"
#include "circleList.h"
#include <stdlib.h>

bool testCreateCircleList()
{
    CircleList* currentElement = createCircleList();
    bool result = currentElement == NULL;
    deleteCircleList(&currentElement);

    return result;
}

bool testCircleListIsEmpty(CircleList** currentPosition)
{
    CircleList* list1 = createCircleList();
    CircleList* list2 = createCircleList();
    push(&list2, 10);
    bool result = circleListIsEmpty(&list1) &&
                  !circleListIsEmpty(&list2);
    deleteCircleList(&list1);
    deleteCircleList(&list2);

    return result;
}

bool testPush(CircleList** currentPosition, Value value);

bool testSwitchToNext(CircleList** currentPosition);

bool testSwitchToN(CircleList** currentPosition, int n);

bool testPopNext(CircleList** currentPosition, int* errorCode);

bool testDeleteCircleList(CircleList** currentPosition)
{
    CircleList* list1 = createCircleList();
    CircleList* list2 = createCircleList();
    push(&list2, 10);
    push(&list2, 20);
    deleteCircleList(&list1);
    deleteCircleList(&list2);

    return list2 == NULL && list1 == NULL;
}

bool testCircleList();