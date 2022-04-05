#include "listTests.h"
#include "list.h"
#include <stdlib.h>

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
    addToHead(head, 1);
    addToHead(head, 2);
    addToHead(head, 3);
    addToHead(head, 4);
    result = result && head != NULL;
    deleteList(&head);

    return result && isListEmpty(head);
}

bool testDeletePosition(void)
{
    List* list = createList();
    addToHead(list, 3);
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
    addToHead(list, 1);
    Position* position = getFirst(list);
    result = result && !isListEmpty(list)
            && getValue(position) == 1;
    deletePosition(&position);
    deleteList(&list);
    return result;
}

bool testAddAfter(void)
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, 1);
    Position* position1 = getFirst(list);
    addAfter(list, position1, 2);
    Position* position2 = getFirst(list);
    result = result && !isListEmpty(list)
            && getValue(position1) == 1
            && getValue(position2) == 1;
    deletePosition(&position1);
    deletePosition(&position2);
    deleteList(&list);
    return result;
}

bool testGetFirst(void)
{
    List* list = createList();
    addToHead(list, 1);
    addToHead(list, 2);
    Position* position2048 = getFirst(list);
    bool result = position2048 != NULL
            && !isLast(position2048)
            && getValue(position2048) == 2;
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testMoveToNext(void)
{
    List* list = createList();
    addToHead(list, 1);
    Position* position2048 = getFirst(list);
    addToHead(list, 2);
    Position* position4096 = getFirst(list);
    moveToNext(position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePositionEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testIsLast(void)
{
    List* list = createList();
    addToHead(list, 1);
    Position* position4096 = getFirst(list);
    addToHead(list, 2);
    addToHead(list, 3);
    bool result = position4096 != NULL
            && isLast(position4096);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testArePointersEqual(void)
{
    List* list = createList();
    addToHead(list, 1);
    Position* position2048 = getFirst(list);
    addToHead(list, 2);
    Position* position4096 = getFirst(list);
    moveToNext(position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePositionEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(&list);
    return result;
}

bool testGetValue(void)
{
    List* list = createList();
    addToHead(list, 1);
    Position* position2048 = getFirst(list);
    bool result = getValue(position2048) == 1;
    deletePosition(&position2048);
    deleteList(&list);
    return result;
}

bool testCopyPointer(void)
{
    List* list = createList();
    addToHead(list, 1);
    Position* position2048 = getFirst(list);
    Position* position4096 = copyPointer(position2048);
    bool result = arePositionEqual(position2048, position4096);
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
            && testGetFirst()&& testMoveToNext()
            && testIsLast() && testArePointersEqual()
            && testCopyPointer();
}