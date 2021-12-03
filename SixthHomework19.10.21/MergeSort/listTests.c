#include <stdlib.h>
#include "listTests.h"
#include "list.h"

bool testCreateList(void)
{
    List* head = createList();
    bool result = head == NULL;
    deleteList(head);

    return result;
}

bool testCreatePosition(void)
{
    Position* position = createPosition();
    bool result = position == NULL;
    deletePosition(position);

    return result;
}

bool testDeleteList(void)
{
    return true;
}

bool testDeletePosition(void)
{
    return true;
}

bool testAddToHead()
{
    return true;
}

bool testAddAfter(void)
{
    return true;
}

bool testGetFirst(void)
{
    return true;
}

bool testGetLast(void)
{
    return true;
}

bool testGetNext(void)
{
    return true;
}

bool testMoveToNext(void)
{
    return true;
}

bool testIsFirst(void)
{
    return true;
}

bool testIsLast(void)
{
    return true;
}

bool testArePointersEqual(void)
{
    return true;
}

bool testCopyValues(void)
{
    return true;
}

bool testChangePriorityValue(void)
{
    return true;
}

bool testGetPriorityValue(void)
{
    return true;
}

bool testCopyPointer(void)
{
    return true;
}

bool testList(void)
{
    return testCreateList() && testCreatePosition()
        && testDeleteList() && testDeletePosition()
        && testAddToHead()
        && testAddAfter() && testGetFirst()
        && testGetLast() && testGetNext()
        && testMoveToNext() && testIsFirst()
        && testIsLast() && testArePointersEqual()
        && testCopyValues() && testChangePriorityValue()
        && testGetPriorityValue() && testCopyPointer();
}