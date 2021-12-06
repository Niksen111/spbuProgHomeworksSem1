#include <string.h>
#include "listTests.h"
#include "list.h"

bool testCreateList(void)
{
    List* head = createList();
    bool result = head != NULL;
    deleteList(head);
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
    addToHead(head, "Lol");
    addToHead(head, "AUU");
    addToHead(head, "God");
    addToHead(head, "KEK");
    result = result && head != NULL;
    deleteList(head);

    return result && isListEmpty(head);
}

bool testDeletePosition(void)
{
    List* list = createList();
    addToHead(list, "Nice");
    Position* position = getFirst(list);
    bool result = position != NULL;
    deletePosition(&position);
    return result && position == NULL;
}

bool testAddToHead()
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM");
    Position* position = getFirst(list);
    result = result && !isListEmpty(list)
            && strcmp("MMM", getValue(position)) == 0;
    deletePosition(&position);
    deleteList(list);
    return result;
}

bool testAddAfter(void)
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM");
    Position* position1 = getFirst(list);
    addAfter(list, position1, "Oleg");
    Position* position2 = getFirst(list);
    result = result && !isListEmpty(list)
            && strcmp("Oleg", getValue(position1)) == 0
            && strcmp("MMMM", getValue(position2)) == 0;
    deletePosition(&position1);
    deletePosition(&position2);
    deleteList(list);
    return result;
}

bool testGetFirst(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    addToHead(list, "AAAA");
    Position* position2048 = getFirst(list);
    bool result = position2048 != NULL
            && strcmp(getValue(position2048), "AAAA") == 0;
    deletePosition(&position2048);
    deleteList(list);
    return result;
}

bool testGetLast(void)
{
    List* list = createList();
    bool result = isListEmpty(list);
    addToHead(list, "MMM");
    addToHead(list, "AAAA");
    addToHead(list, "LOL");
    Position* position4096 = getLast(list);
    result = result && position4096 != NULL
            && isLast(position4096);
    deletePosition(&position4096);
    deleteList(list);
    return result;
}

bool testMoveToNext(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    Position* position2048 = getFirst(list);
    addToHead(list, "GSfdgdfg");
    Position* position4096 = getFirst(list);
    moveToNext(&position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(list);
    return result;
}

bool testIsLast(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    addToHead(list, "AAAA");
    addToHead(list, "Hochu");
    Position* position4096 = getLast(list);
    bool result = position4096 != NULL
            && isLast(position4096);
    deletePosition(&position4096);
    deleteList(list);
    return result;
}

bool testArePointersEqual(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    Position* position2048 = getFirst(list);
    addToHead(list, "AFFFF");
    Position* position4096 = getFirst(list);
    moveToNext(&position4096);
    bool result = position2048 != NULL && position4096 != NULL
            && arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(list);
    return result;
}

bool testGetValue(void)
{
    List* list = createList();
    addToHead(list, "God");
    Position* position2048 = getFirst(list);
    bool result = strcmp(getValue(position2048), "God") == 0;
    deletePosition(&position2048);
    deleteList(list);
    return result;
}

bool testCopyPointer(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    Position* position2048 = getFirst(list);
    Position* position4096 = copyPointer(position2048);
    bool result = arePointersEqual(position2048, position4096);
    deletePosition(&position2048);
    deletePosition(&position4096);
    deleteList(list);
    return result;
}

bool testIsListEmpty(void)
{
    List* head = createList();
    bool result = isListEmpty(head);
    deleteList(head);
    return result;
}

bool testIncreaseCounter(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    Position* position2048 = getFirst(list);
    increaseCounter(position2048);
    increaseCounter(position2048);
    bool result = getCounter(position2048) == 2;
    deletePosition(&position2048);
    deleteList(list);

    return result;
}

bool testGetCounter(void)
{
    List* list = createList();
    addToHead(list, "MMM");
    Position* position2048 = getFirst(list);
    increaseCounter(position2048);
    increaseCounter(position2048);
    increaseCounter(position2048);
    bool result = getCounter(position2048) == 3;
    deletePosition(&position2048);
    deleteList(list);

    return result;
}

bool testList(void)
{
    return testCreateList() && testCreatePosition()
            && testDeleteList() && testDeletePosition()
            && testAddToHead() && testAddAfter()
            && testGetFirst() && testGetLast()
            && testMoveToNext() && testIsLast()
            && testArePointersEqual() && testCopyPointer()
            && testGetValue() && testIsListEmpty()
            && testIncreaseCounter() && testGetCounter();
}