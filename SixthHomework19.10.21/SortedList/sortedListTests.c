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
    SortedList* stack1 = createSortedList();
    SortedList* stack2 = createSortedList();
    push(&stack2, 10);
    bool result = sortedListIsEmpty(&stack1) &&
                  !sortedListIsEmpty(&stack2);
    deleteSortedList(&stack1);
    deleteSortedList(&stack2);

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
        result = result && list1->value == array1Answer[i];
        list1 = list1->next;
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

bool testSortedList()
{
    return testSortedListIsEmpty() && testPush() &&
        testCreateSortedList() &&testRemoveTheItem() &&
        testDeleteSortedList() && testRemoveItemFromHead();
}