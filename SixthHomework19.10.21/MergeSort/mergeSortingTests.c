#include "mergeSortingTests.h"
#include "list.h"
#include "mergeSorting.h"
#include <string.h>
#include <stdlib.h>
#include "supportFunctions.h"

bool checkThatListAreSorted(List* list, Priority priority)
{
    Position* position1 = first(list);
    if (position1 == NULL)
    {
        return false;
    }
    if (isLast(position1))
    {
        return true;
    }
    Position* position2 = getNext(position1);
    while (!isLast(position1))
    {
        if (!isFirstEarlier(getPriorityValue(position1, priority),
                getPriorityValue(position2, priority)))
        {
            free(position1);
            free(position2);
            return false;
        }
    }
    free(position1);
    free(position2);
    return true;
}

bool testMergeSorting()
{
    List* list1 = createList();
    Position* position1 = createPosition();
    char name1[30] = "dEfgh";
    char phone1[30] = "12345";
    char name2[30] = "eFghc";
    char phone2[30] = "12345";
    char name3[30] = "Cdefg";
    char phone3[30] = "12345";
    char name4[30] = "abcdef";
    char phone4[30] = "12345";
    char name5[30] = "bcdef";
    char phone5[30] = "12345";
    addAfter(&list1, &position1, name1, phone1);
    addAfter(&list1, &position1, name2, phone2);
    addAfter(&list1, &position1, name3, phone3);
    addAfter(&list1, &position1, name4, phone4);
    addAfter(&list1, &position1, name5, phone5);
    mergeSorting(&list1, name);
    bool result = checkThatListAreSorted(list1, name);
    mergeSorting(&list1, phone);
    result = result && checkThatListAreSorted(list1, phone);
    deleteList(list1);
    free(position1);

    return result;
}