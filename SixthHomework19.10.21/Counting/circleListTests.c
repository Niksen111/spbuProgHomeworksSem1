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

bool testCircleListIsEmpty()
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

bool testPush()
{
    CircleList* list1 = createCircleList();
    for (int i = 0; i < 7; ++i)
    {
        push(&list1, i);
    }
    bool result = true;
    switchToNext(&list1);
    for (int i = 0; i < 7; ++i)
    {
        result = result && (list1->value) == i;
        switchToNext(&list1);
    }
    deleteCircleList(&list1);

    return result;
}

bool testSwitchToNext()
{
    CircleList* list1 = createCircleList();
    for (int i = 0; i < 5; ++i)
    {
        push(&list1, i);
    }
    bool result = (list1->value) == 4;
    for (int i = 0; i < 4; ++i)
    {
        switchToNext(&list1);
        result = result && (list1->value) == i;
    }
    deleteCircleList(&list1);

    return result;
}

bool testSwitchToN()
{
    CircleList* list1 = createCircleList();
    for (int i = 0; i < 7; ++i)
    {
        push(&list1, i);
    }
    switchToNext(&list1);
    bool result = true;
    int arrayAnswers[5] = { 3, 1, 6, 6, 2 };
    int arrayN[5] = { 3, 5, 5, 14, 10};
    for (int i = 0; i < 5; ++i)
    {
        switchToN(&list1, arrayN[i]);
        result = result && (list1->value) == arrayAnswers[i];
    }
    deleteCircleList(&list1);
    return result;
}

bool testPopNext()
{
    CircleList* list1 = createCircleList();
    for (int i = 0; i < 10; ++i)
    {
        push(&list1, i);
    }
    bool result = true;
    int errorCode = 0;
    result = result && popNext(&list1, &errorCode) == 0
            && errorCode == 0;
    switchToN(&list1, 4);
    result = result && popNext(&list1, &errorCode) == 5
            && errorCode == 0;
    switchToN(&list1, 2);
    result = result && popNext(&list1, &errorCode) == 8
             && errorCode == 0;
    CircleList* m = list1;
    while (m->next != list1)
    {
        result = result && !((m->value) == 0 || (m->value) == 5 || (m->value) == 8);
        switchToNext(&m);
    }
    deleteCircleList(&list1);
    result = result && popNext(&list1, &errorCode) == 0 && errorCode == -1;

    return result;
}

bool testDeleteCircleList()
{
    CircleList* list1 = createCircleList();
    CircleList* list2 = createCircleList();
    push(&list2, 10);
    push(&list2, 20);
    deleteCircleList(&list1);
    deleteCircleList(&list2);

    return list2 == NULL && list1 == NULL;
}

bool testCircleList()
{
    return testPush() && testCircleListIsEmpty()
        && testCreateCircleList() && testDeleteCircleList()
        && testPopNext() && testSwitchToN()
        && testSwitchToNext();
}