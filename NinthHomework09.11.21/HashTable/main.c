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

bool testCreateHashTableFromFile(void)
{
    HashTable* hashTable1 = createHashTableFromFile("file.txt");
    bool result = giveNumberOfRepetitionsOfWord(hashTable1, "hello") == 3;
    deleteHashTable(&hashTable1);
    HashTable* hashTable2 = createHashTableFromFile("test.txt");
    result = result && giveNumberOfRepetitionsOfWord(hashTable2, "The") == 30;
    deleteHashTable(&hashTable2);
    return result;
}

int main()
{
    if (!testList() || !testCreateHashTableFromFile())
    {
        printf("Tests failed(\n");
        return -1;
    }
    HashTable* myTable = createHashTableFromFile("test.txt");
    printTableStatistics(myTable);
    deleteHashTable(&myTable);
    return 0;
}
