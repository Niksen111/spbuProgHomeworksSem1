#include <string.h>
#include "listTests.h"
#include "list.h"

bool testCreateList(void)
{
    List* head = createList();
    bool result = head != NULL;
    deleteList(&head);
    return result;
}

bool testCreatePosition(void)
{
    Position* position = createPosition();
    bool result = position != NULL;
    deletePosition(&position);

    return result;
}

bool testDeleteList(void)
{
    List* head = createList();
    bool result = head != NULL;
    addToHead(head, "Lol", "Kek");
    addToHead(head, "AUU", "Nice");
    addToHead(head, "God", "AAAAAA");
    addToHead(head, "I want", "to sleep");
    result = result && head != NULL;
    deleteList(&head);

    return result && isListEmpty(head);
}

bool testDeletePosition(void)
{
    List* list = createList();
    addToHead(list, "Nice", "Day");
    Position* position = getFirst(list);
    bool result = position != NULL;
    deletePosition(&position);
    deleteList(&list);

    return result && position == NULL;
}

bool testAddToHead()
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM", "MMMM");
    Position* position = getFirst(list);
    result = result && !isListEmpty(list)
            && strcmp("MMM", getPriorityValue(position, name)) == 0;
    deletePosition(&position);
    deleteList(&list);
    return result;
}

bool testAddAfter(void)
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM", "MMMM");
    Position* position1 = getFirst(list);
    addAfter(list, position1, "Oleg", "Oleeeee");
    Position* position2 = getFirst(list);
    result = result && !isListEmpty(list)
            && strcmp("Oleg", getPriorityValue(position1, name)) == 0
            && strcmp("MMMM", getPriorityValue(position2, phone)) == 0;
    deletePosition(&position1);
    deletePosition(&position2);
    deleteList(&list);
    return result;
}

bool testGetFirst(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    addToHead(list, "AAAA", "AAAAAAA");
    Position* position2048 = getFirst(list);
    bool result = position2048 != NULL
            && isFirst(position2048, list);
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testGetLast(void)
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM", "MMMM");
    addToHead(list, "AAAA", "AAAAAAA");
    addToHead(list, "Hochu", "Domoi");
    Position* position4096 = getLast(list);
    result = result && position4096 != NULL
            && isLast(position4096);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testMoveToNext(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    Position* position2048 = getFirst(list);
    addToHead(list, "Hochu", "Domoi");
    Position* position4096 = getFirst(list);
    moveToNext(&position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testIsFirst(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    addToHead(list, "AAAA", "AAAAAAA");
    Position* position2048 = getFirst(list);
    bool result = position2048 != NULL
            && isFirst(position2048, list);
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testIsLast(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    addToHead(list, "AAAA", "AAAAAAA");
    addToHead(list, "Hochu", "Domoi");
    Position* position4096 = getLast(list);
    bool result = position4096 != NULL
            && isLast(position4096);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testArePointersEqual(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    Position* position2048 = getFirst(list);
    addToHead(list, "Hochu", "Domoi");
    Position* position4096 = getFirst(list);
    moveToNext(&position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testChangePriorityValue(void)
{
    List* list = createList();
    addToHead(list, "God", "Nooooo");
    Position* position2048 = getFirst(list);
    changePriorityValue(position2048, "AAAAAAAA", phone);
    bool result = strcmp(getPriorityValue(position2048, phone), "AAAAAAAA") == 0;
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testGetPriorityValue(void)
{
    List* list = createList();
    addToHead(list, "God", "Nooooo");
    Position* position2048 = getFirst(list);
    bool result = strcmp(getPriorityValue(position2048, name), "God") == 0
            && strcmp(getPriorityValue(position2048, phone), "Nooooo") == 0;
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testCopyPointer(void)
{
    List* list = createList();
    addToHead(list, "MMM", "MMMM");
    Position* position2048 = getFirst(list);
    Position* position4096 = copyPointer(position2048);
    bool result = arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testList(void)
{
    return testCreateList() && testCreatePosition()
        && testDeleteList() && testDeletePosition()
        && testAddToHead() && testAddAfter()
        && testGetFirst() && testGetLast()
        && testMoveToNext() && testIsFirst()
        && testIsLast() && testArePointersEqual()
        && testChangePriorityValue()
        && testGetPriorityValue() && testCopyPointer();
}