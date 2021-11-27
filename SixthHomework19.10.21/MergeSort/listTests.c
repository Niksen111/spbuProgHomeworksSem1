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

}

bool testDeletePosition(void)
{

}

bool testAddAfter(void)
{

}

bool testGetFirst(void)
{

}

bool testGetLast(void)
{

}

bool testGetNext(void)
{

}

bool testMoveToNext(void)
{

}

bool testIsFirst(void)
{

}

bool testIsLast(void)
{

}

bool testArePointersEqual(void)
{

}

bool testCopyValues(void)
{

}

bool testChangePriorityValue(void)
{

}

bool testGetPriorityValue(void)
{

}

bool testCopyPointer(void)
{

}

bool testList(void)
{
    return testCreateList() && testCreatePosition()
        && testDeleteList() && testDeletePosition()
        && testAddAfter() && testGetFirst()
        && testGetLast() && testGetNext()
        && testMoveToNext() && testIsFirst()
        && testIsLast() && testArePointersEqual()
        && testCopyValues() && testChangePriorityValue()
        && testGetPriorityValue() && testCopyPointer();
}