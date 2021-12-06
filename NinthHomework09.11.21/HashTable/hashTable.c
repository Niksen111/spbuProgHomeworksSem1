#include "hashTable.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct HashTable
{
    List* hashTable[1553];
} HashTable;

HashTable* createHashTable()
{
    return calloc(1, sizeof(HashTable));
}

int calculateHashFunction(char* line)
{
    int result = 0;
    int length = strlen(line);
    int currentMultiplier = 1;
    int mod = 1553;
    for (int i = 0; i < length; ++i)
    {
        result = (result + abs((((int)line[i]) * currentMultiplier) % mod)) % mod;
        if (currentMultiplier > 1000000000)
        {
            currentMultiplier = 1;
        }
        else
        {
            currentMultiplier *= 3;
        }
    }
    return result;
}

void addToHashTable(HashTable* hashTable, char* line)
{
    int i = calculateHashFunction(line);
    if (hashTable->hashTable[i] == NULL)
    {
        hashTable->hashTable[i] = createList();
        addToHead(hashTable->hashTable[i], line);
        Position* position = getFirst(hashTable->hashTable[i]);
        increaseCounter(position);
        deletePosition(&position);
    }
    else
    {
        Position* position = getFirst(hashTable->hashTable[i]);
        while (strcmp(getValue(position), line) != 0 && !isLast(position))
        {
            moveToNext(&position);
        }
        if (strcmp(getValue(position), line) == 0)
        {
            increaseCounter(position);
            deletePosition(&position);
        }
        else
        {
            addAfter(hashTable->hashTable[i], position, line);
            moveToNext(&position);
            increaseCounter(position);
            deletePosition(&position);
        }
    }
}

void printTableStatistics(HashTable* hashTable)
{
    int voidCounter = 0;
    int listLengths = 0;
    int maxListLength = 0;
    for (int i = 0; i < 1553; ++i)
    {
        if (hashTable->hashTable[i] != NULL)
        {
            Position* position = getFirst(hashTable->hashTable[i]);
            int currentLength = 0;
            while(!isLast(position))
            {
                ++currentLength;
                ++listLengths;
                moveToNext(&position);
            }
            ++currentLength;
            ++listLengths;
            maxListLength = currentLength > maxListLength ? currentLength : maxListLength;
            deletePosition(&position);
        }
        else
        {
            ++voidCounter;
        }
    }
    printf("Table occupancy rate - %lf\n", (double) (voidCounter) / (double) 1553);
    printf("Average list length - %lf\n", (double) (listLengths) / (double) 1553);
    printf("Maximum list length - %d\n", maxListLength);
}

void deleteHashTable(HashTable** hashTable)
{
    for (int i = 0; i < 1553; ++i)
    {
        deleteList((*hashTable)->hashTable[i]);
        free((*hashTable)->hashTable[i]);
    }
    free(*hashTable);
}

void printHashTable(HashTable* hashTable)
{
    for (int i = 0; i < 1553; ++i)
    {
        if (hashTable->hashTable[i] != NULL)
        {
            Position* position = getFirst(hashTable->hashTable[i]);
            while(!isLast(position))
            {
                printf("%s - %d\n", getValue(position), getCounter(position));
                moveToNext(&position);
            }
            printf("%s - %d\n", getValue(position), getCounter(position));
            deletePosition(&position);
        }
    }
}