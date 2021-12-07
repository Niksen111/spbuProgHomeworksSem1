#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "listTests.h"

HashTable* createHashTableFromFile(char name[])
{
    FILE* file = fopen(name, "r");
    HashTable* hashTable = createHashTable(1553);
    while (!feof(file))
    {
        char* buffer = calloc(100, sizeof(char));
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0)
        {
            break;
        }
        addToHashTable(hashTable, buffer, 1);
    }
    recalculateTableStatistics(hashTable);
    redoHashTable(&hashTable);
    recalculateTableStatistics(hashTable);
    fclose(file);
    return hashTable;
}

int main()
{
    if (!testList())
    {
        printf("Tests failed(\n");
        return -1;
    }
    HashTable* myTable = createHashTableFromFile("test.txt");
    printTableStatistics(myTable);
    //printHashTable(myTable);
    deleteHashTable(&myTable);
    return 0;
}
