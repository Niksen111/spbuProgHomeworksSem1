#include "mergeSorting.h"
#include <stdlib.h>
#include <string.h>
#include "supportFunctions.h"
#include "list.h"

int getLengthPartOfList(Position* start, Position* end)
{
    if (start == NULL)
    {
        return 0;
    }
    Position* position = copyPointer(start);
    if (position == NULL)
    {
        return -1;
    }
    int counter = 0;
    while (!arePointersEqual(position, end))
    {
        if (position == NULL)
        {
            deletePosition(&position);
            return -1;
        }
        ++counter;
        moveToNext(&position);
    }
    ++counter;
    deletePosition(&position);
    return counter;
}

int getLengthOfList(List* list)
{
    Position* position = getFirst(list);
    int counter = 0;
    while (!isLast(position))
    {
        ++counter;
        moveToNext(&position);
    }
    ++counter;
    free(position);
    return counter;
}


int mergeSortingRecursive(List** list, List** buffer, Position* leftBoarder,
                   Position* rightBoarder, Priority priority)
{
    if (arePointersEqual(leftBoarder, rightBoarder))
    {
        return -1;
    }
    int lengthOfSegment = getLengthPartOfList(leftBoarder, rightBoarder);
    Position* newRightBoarder = copyPointer(leftBoarder);
    if (newRightBoarder == NULL)
    {
        return -2;
    }
    for (int i = 0; i < lengthOfSegment / 2 - 1; ++i)
    {
        moveToNext(&newRightBoarder);
    }
    Position* newLeftBoarder = copyPointer(newRightBoarder);
    moveToNext(&newLeftBoarder);
    mergeSortingRecursive(list, buffer, leftBoarder, newRightBoarder, priority);
    // need to copy the value from the buffer to the sheet
    mergeSortingRecursive(list, buffer, newLeftBoarder, rightBoarder, priority);
    // need to copy the value from the buffer to the sheet
    Position* start1 = copyPointer(leftBoarder);
    Position* start2 = copyPointer(newLeftBoarder);
    Position* myBuffer = NULL;
    moveToNext(&newRightBoarder);
    Position* position = copyPointer(rightBoarder);
    moveToNext(&position);
    while (!arePointersEqual(start1, newRightBoarder)
        || !arePointersEqual(start2, position))
    {
        if (myBuffer == NULL)
        {
            myBuffer = getFirst(*buffer);
        }
        else
        {
            moveToNext(&myBuffer);
        }
        if (arePointersEqual(start1, newRightBoarder))
        {
            copyValues(myBuffer, start2);
            moveToNext(&start2);
        }
        else if (arePointersEqual(start2, position))
        {
            copyValues(myBuffer, start1);
            moveToNext(&start1);
        }
        else if (isFirstEarlier(getPriorityValue(start1, priority),
                getPriorityValue(start2, priority)))
        {
            copyValues(myBuffer, start1);
            moveToNext(&start1);
        }
        else
        {
            copyValues(myBuffer, start2);
            moveToNext(&start2);
        }
    }
    free(newRightBoarder);
    free(newLeftBoarder);
    free(start1);
    free(start2);
    free(myBuffer);
}

int mergeSorting(List** list, Priority priority)
{
    int lengthOfList = getLengthOfList(*list);
    List* buffer = createList();
    for (int i = 0; i < lengthOfList - 1; ++i)
    {
        addToHead(buffer, NULL, NULL);
    }
    Position* leftBoarder = getFirst(*list);
    Position* rightBoarder = getLast(*list);
    int errorCode = mergeSortingRecursive(list, &buffer, leftBoarder,
            rightBoarder, priority);
    free(leftBoarder);
    free(rightBoarder);
    deleteList(buffer);

    return errorCode;
}