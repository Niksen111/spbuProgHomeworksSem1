#include "list.h"
#include "listTests.h"
#include <stdio.h>

List* getMaxIncreasingSequence(List* list)
{
    if (list == NULL || isListEmpty(list))
    {
        return NULL;
    }
    Position* position = getFirst(list);
    int currentLength = 0;
    int maxLength = 0;
    int indexOfMaxSequence = 0;
    int i = 0;
    int indexOfCurrentSequence = 0;
    int lastElement = 0;
    while (!isLast(position))
    {
        if (currentLength == 0)
        {
            ++currentLength;
            indexOfCurrentSequence = i;
            lastElement = getValue(position);
        }
        else if (getValue(position) > lastElement)
        {
            ++currentLength;
            lastElement = getValue(position);
        }
        else
        {
            currentLength = 1;
            indexOfCurrentSequence = i;
            lastElement = getValue(position);
        }
        if (currentLength > maxLength)
        {
            indexOfMaxSequence = indexOfCurrentSequence;
            maxLength = currentLength;
        }
        ++i;
        moveToNext(position);
    }
    if (currentLength == 0)
    {
        ++currentLength;
        indexOfCurrentSequence = i;
        lastElement = getValue(position);
    }
    else if (getValue(position) > lastElement)
    {
        ++currentLength;
        lastElement = getValue(position);
    }
    else
    {
        currentLength = 1;
        indexOfCurrentSequence = i;
        lastElement = getValue(position);
    }
    if (currentLength > maxLength)
    {
        indexOfMaxSequence = indexOfCurrentSequence;
        maxLength = currentLength;
    }
    deletePosition(&position);
    List* newList = createList();
    position = getFirst(list);
    for (int j = 0; j < indexOfMaxSequence; ++j)
    {
        moveToNext(position);
    }
    addToHead(newList, getValue(position));
    moveToNext(position);
    Position* newPosition = getFirst(newList);
    for (int j = 0; j < maxLength - 1; ++j)
    {
        addAfter(newList, newPosition, getValue(position));
        moveToNext(position);
        moveToNext(newPosition);
    }
    deletePosition(&position);
    deletePosition(&newPosition);

    return newList;
}

void printList(List* list)
{
    if (isListEmpty(list))
    {
        return;
    }
    Position* position = getFirst(list);
    while (!isLast(position))
    {
        printf("%d, ", getValue(position));
        moveToNext(position);
    }
    printf("%d\n", getValue(position));
    deletePosition(&position);
}

bool testGetMaxIncreasingSequence()
{
    List* list1 = createList();
    addToHead(list1, 100);
    Position* position1 = getFirst(list1);
    for (int i = 0; i < 10; ++i)
    {
        addAfter(list1, position1, i);
        moveToNext(position1);
    }
    for (int i = 9; i < 15; ++i)
    {
        addAfter(list1, position1, i);
        moveToNext(position1);
    }
    deletePosition(&position1);
    List* list1Result = getMaxIncreasingSequence(list1);
    Position* position1Result = getFirst(list1Result);
    int i = 1;
    int lastElement = getValue(position1Result);
    bool result = lastElement == 0;
    moveToNext(position1Result);
    while (!isLast(position1Result))
    {
        ++i;
        result = result && getValue(position1Result) > lastElement;
        lastElement = getValue(position1Result);
        moveToNext(position1Result);
    }
    ++i;
    result = result && getValue(position1Result) == 9
            && getValue(position1Result) > lastElement
            && i == 10;
    deletePosition(&position1Result);
    deleteList(&list1);
    deleteList(&list1Result);

    return result;
}

int main()
{
    if (!testGetMaxIncreasingSequence() || !testList())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    printf("All ok :)\n");
    return 0;
}
