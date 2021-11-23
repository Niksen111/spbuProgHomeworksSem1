#include <stdio.h>
#include "list.h"

void printList(List* list)
{
    if (isListEmpty(list) || list == NULL)
    {
        return;
    }
    Position* position = getFirst(list);
    while (!isLast(position))
    {
        printf("%d ", getValue(position));
        moveToNext(&position);
    }
    printf("%d\n", getValue(position));
    deletePosition(position);
}

List* writeFileValuesToList(char fileName[], int* errorCode)
{
    FILE* file = fopen(fileName, "r");
    int value = 0;
    List* list = createList();
    Position* position = createPosition();
    while (fscanf(file, "%d", &value) >= 0)
    {
        add(&list, &position, value);
        while (!isLast(position))
        {
            moveToNext(&position);
        }
    }
    fclose(file);
    deletePosition(position);
    return list;
}

void swapValues(Position* first, Position* second)
{
    int value = getValue(first);
    changeValue(first, getValue(second));
    changeValue(second, value);
}

int expandList(List* list)
{
    if (list == NULL || isListEmpty(list))
    {
        return 0;
    }
    Position* rightBoarder = getFirst(list);
    if (isLast(rightBoarder))
    {
        deletePosition(rightBoarder);
        return 0;
    }
    while (!isLast(rightBoarder))
    {
        moveToNext(&rightBoarder);
    }
    Position* leftBoarder = getFirst(list);
    swapValues(leftBoarder, rightBoarder);
    while (true)
    {
        if (arePointersEqual(leftBoarder, rightBoarder)
            || areNeighbors(leftBoarder, rightBoarder))
        {
            deletePosition(leftBoarder);
            deletePosition(rightBoarder);
            return 0;
        }
        moveToNext(&leftBoarder);
        Position* currentPosition = copyPointer(leftBoarder);
        while (!areNeighbors(currentPosition, rightBoarder))
        {
            moveToNext(&currentPosition);
        }
        deletePosition(rightBoarder);
        rightBoarder = currentPosition;
        swapValues(leftBoarder, rightBoarder);
    }
}

bool testWriteFileValuesToList()
{
    FILE* testFile1 = fopen("testFile1.txt", "w");
    int testArray[9] = { 0 };
    for (int i = 0; i < 9; ++i)
    {
        testArray[i] = i;
        fprintf(testFile1, "%d ", i);
    }
    fclose(testFile1);
    int errorCode = 0;
    List* testList = writeFileValuesToList("testFile1.txt", &errorCode);
    Position* position = getFirst(testList);
    for (int i = 0; i < 9; ++i)
    {
        if (getValue(position) != testArray[i])
        {
            deleteList(testList);
            return false;
        }
        moveToNext(&position);
    }
    return true;
}

bool testSwapValues()
{
    List* list = createList();
    Position* position1 = createPosition();
    add(&list, &position1, 1);
    add(&list, &position1, 2);
    Position* position2 = getFirst(list);
    moveToNext(&position2);
    swapValues(position1, position2);
    bool result = getValue(position1) == 2
            && getValue(position2) == 1;
    deletePosition(position1);
    deletePosition(position2);
    deleteList(list);
    return result;
}

bool testExpandList()
{
    FILE* testFile1 = fopen("testFile1.txt", "w");
    int testArray[9] = { 0 };
    for (int i = 0; i < 9; ++i)
    {
        testArray[8 - i] = i;
        fprintf(testFile1, "%d ", i);
    }
    fclose(testFile1);
    int errorCode = 0;
    List* testList = writeFileValuesToList("testFile1.txt", &errorCode);
    expandList(testList);
    Position* position = getFirst(testList);
    bool result = true;
    for (int i = 0; i < 9 && !isLast(position); ++i)
    {
        result = result && getValue(position) == testArray[i];
        moveToNext(&position);
    }
    deletePosition(position);
    deleteList(testList);
    return result;
}

int main()
{
    if (!testWriteFileValuesToList() || !testSwapValues() || !testExpandList())
    {
        printf("Tests failed(\n");
        return -1;
    }
    int errorCode = 0;
    List* list = writeFileValuesToList("numbers.txt", &errorCode);
    printList(list);
    expandList(list);
    printList(list);
    deleteList(list);
    return 0;
}
