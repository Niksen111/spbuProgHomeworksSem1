#include "circleListTests.h"
#include "circleList.h"
#include <stdlib.h>

bool testCreateCircleList()
{
    CircleListRoot* currentElement = createCircleList();
    bool result = currentElement == NULL;
    deleteCircleList(&currentElement);

    return result;
}

bool testCircleListIsEmpty()
{
    CircleListRoot* list1 = createCircleList();
    CircleListRoot* list2 = createCircleList();
    push(&list2, 10);
    bool result = circleListIsEmpty(list1) &&
                  !circleListIsEmpty(list2);
    deleteCircleList(&list1);
    deleteCircleList(&list2);

    return result;
}

bool testPush()
{
    CircleListRoot* list1 = createCircleList();
    for (int i = 0; i < 7; ++i)
    {
        push(&list1, i);
    }
    bool result = true;
    switchRootToNext(&list1);
    for (int i = 0; i < 7; ++i)
    {
        int errorCode = 0;
        result = result && getCurrentPositionValue(list1, &errorCode) == i;
        if (errorCode != 0)
        {
            deleteCircleList(&list1);
            return false;
        }
        switchRootToNext(&list1);
    }
    deleteCircleList(&list1);

    return result;
}

bool testswitchRootToNext()
{
    CircleListRoot* list1 = createCircleList();
    for (int i = 0; i < 5; ++i)
    {
        push(&list1, i);
    }
    int errorCode = 0;
    bool result = getCurrentPositionValue(list1, &errorCode) == 4;
    if (errorCode != 0)
    {
        deleteCircleList(&list1);
        return false;
    }
    for (int i = 0; i < 4; ++i)
    {
        switchRootToNext(&list1);
        result = result && getCurrentPositionValue(list1, &errorCode) == i;
        if (errorCode != 0)
        {
            deleteCircleList(&list1);
            return false;
        }
    }
    deleteCircleList(&list1);

    return result;
}

bool testmoveNPositionsForward()
{
    CircleListRoot* list1 = createCircleList();
    for (int i = 0; i < 7; ++i)
    {
        push(&list1, i);
    }
    switchRootToNext(&list1);
    bool result = true;
    int arrayAnswers[5] = { 3, 1, 6, 6, 2 };
    int arrayN[5] = { 3, 5, 5, 14, 10 };
    for (int i = 0; i < 5; ++i)
    {
        moveNPositionsForward(&list1, arrayN[i]);
        int errorCode = 0;
        result = result && getCurrentPositionValue(list1, &errorCode) == arrayAnswers[i];
        if (errorCode != 0)
        {
            deleteCircleList(&list1);
            return false;
        }
    }
    deleteCircleList(&list1);
    return result;
}

bool testPopNext()
{
    CircleListRoot* list1 = createCircleList();
    for (int i = 0; i < 10; ++i)
    {
        push(&list1, i);
    }
    int errorCode = 0;
    bool result = popNext(&list1, &errorCode) == 0
            && errorCode == 0;
    moveNPositionsForward(&list1, 4);
    result = result && popNext(&list1, &errorCode) == 5
            && errorCode == 0;
    moveNPositionsForward(&list1, 2);
    result = result && popNext(&list1, &errorCode) == 8
             && errorCode == 0;
    CircleListRoot* m = list1;
    while (getNext(m, &errorCode) != list1)
    {
        result = result && !(getCurrentPositionValue(m, &errorCode) == 0
                && errorCode == 0
                || getCurrentPositionValue(m, &errorCode) == 5
                && errorCode == 0
                || getCurrentPositionValue(m, &errorCode) == 8
                && errorCode == 0);
        switchRootToNext(&m);
    }
    deleteCircleList(&list1);
    result = result && popNext(&list1, &errorCode) == 0 && errorCode == -1;

    return result;
}

bool testDeleteCircleList()
{
    CircleListRoot* list1 = createCircleList();
    CircleListRoot* list2 = createCircleList();
    push(&list2, 10);
    push(&list2, 20);
    deleteCircleList(&list1);
    deleteCircleList(&list2);

    return list2 == NULL && list1 == NULL;
}

bool testGetCurrentPositionValue()
{
    CircleListRoot* list1 = createCircleList();
    for (int i = 0; i < 5; ++i)
    {
        push(&list1, i);
    }
    bool result = true;
    switchRootToNext(&list1);
    for (int i = 0; i < 5; ++i)
    {
        int errorCode = 0;
        result = result && getCurrentPositionValue(list1, &errorCode) == i
                && errorCode == 0;
        switchRootToNext(&list1);
    }
    deleteCircleList(&list1);
    int errorCode = 0;
    result = result && getCurrentPositionValue(list1, &errorCode) == 0
            && errorCode != 0;

    return result;
}

bool testGetNext()
{
    CircleListRoot* list = createCircleList();
    int errorCode = 0;
    bool result = getNext(list, &errorCode) == NULL && errorCode != 0;
    push(&list, 5);
    result = result && getNext(list, &errorCode) == list && errorCode == 0;
    deleteCircleList(&list);

    return result;
}

bool testCircleList()
{
    return testPush() && testCircleListIsEmpty()
        && testCreateCircleList() && testDeleteCircleList()
        && testPopNext() && testmoveNPositionsForward()
        && testswitchRootToNext() && testGetCurrentPositionValue()
        && testGetNext();
}