#include "sortedListTests.h"
#include "sortedList.h"
#include <stdlib.h>

bool testCreateSortedList()
{
    SortedList * head = createSortedList();
    bool result = head == NULL;
    deleteSortedList(&head);

    return result;
}

bool testSortedListIsEmpty()
{
    SortedList* list1 = createSortedList();
    SortedList* list2 = createSortedList();
    push(&list2, 10);
    bool result = sortedListIsEmpty(&list1) &&
            !sortedListIsEmpty(&list2);
    deleteSortedList(&list1);
    deleteSortedList(&list2);

    return result;
}

bool testPush()
{
    SortedList* list1 = createSortedList();
    push(&list1, 5);
    push(&list1, -5);
    push(&list1, 15);
    push(&list1, -15);
    int array1Answer[4] = { -15, -5, 5, 15 };
    bool result = true;
    for (int i = 0; !sortedListIsEmpty(&list1); ++i)
    {
        int errorCode = 0;
        result = result && getValueFromHead(list1, &errorCode) ==
                array1Answer[i];
        if (errorCode != 0)
        {
            deleteSortedList(&list1);
            return false;
        }
        removeItemFromHead(&list1, &errorCode);
        if (errorCode != 0)
        {
            deleteSortedList(&list1);
            return false;
        }
    }
    deleteSortedList(&list1);

    return result;
}

bool testRemoveItemFromHead()
{
    SortedList* head = createSortedList();
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    int errorCode = 0;
    bool result = removeItemFromHead(&head, &errorCode) == 10 &&
                removeItemFromHead(&head, &errorCode) == 20 &&
                removeItemFromHead(&head, &errorCode) == 30 &&
                removeItemFromHead(&head, &errorCode) == 0 &&
                errorCode == -1;
    deleteSortedList(&head);

    return result;
}

bool testRemoveTheItem()
{
    SortedList* list1 = createSortedList();
    push(&list1, 5);
    push(&list1, -5);
    push(&list1, 15);
    push(&list1, -15);
    bool result = removeTheItem(&list1, 5) == 0 &&
                removeTheItem(&list1, 5) == -1 &&
                removeTheItem(&list1, 2) == -1 &&
                removeTheItem(&list1, 15) == 0 &&
                removeTheItem(&list1, 15) == -1 &&
                removeTheItem(&list1, -15) == 0 &&
                removeTheItem(&list1, -15) == -1 &&
                !sortedListIsEmpty(&list1) &&
                removeTheItem(&list1, -5) == 0 &&
                removeTheItem(&list1, -5) == -1 &&
                sortedListIsEmpty(&list1);
    deleteSortedList(&list1);

    return result;
}

bool testDeleteSortedList()
{
    SortedList* list1 = createSortedList();
    SortedList* list2 = createSortedList();
    push(&list2, 10);
    push(&list2, 20);
    deleteSortedList(&list1);
    deleteSortedList(&list2);

    return list2 == NULL && list1 == NULL;
}

bool testGetValueFromHead()
{
    SortedList* list1 = createSortedList();
    push(&list1, 5);
    push(&list1, -5);
    push(&list1, 15);
    push(&list1, -15);
    int errorCode = 0;
    bool result = getValueFromHead(list1, &errorCode) == -15
            && errorCode == 0;
    removeItemFromHead(&list1, &errorCode);
    result = result && getValueFromHead(list1, &errorCode) == -5
            && errorCode == 0;
    removeItemFromHead(&list1, &errorCode);
    result = result && getValueFromHead(list1, &errorCode) == 5
            && errorCode == 0;
    removeItemFromHead(&list1, &errorCode);
    result = result && getValueFromHead(list1, &errorCode) == 15
            && errorCode == 0;
    removeItemFromHead(&list1, &errorCode);
    result = result && getValueFromHead(list1, &errorCode) == 0
            && errorCode == -1;
    deleteSortedList(&list1);

    return result;
}

bool testSortedList()
{
    return testSortedListIsEmpty() && testPush()
        && testCreateSortedList() && testRemoveTheItem()
        && testDeleteSortedList() && testRemoveItemFromHead()
        && testGetValueFromHead();
}