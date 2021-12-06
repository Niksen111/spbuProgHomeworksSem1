#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"

HashTable* createHashTableFromFile(char name[])
{
    FILE* file = fopen(name, "r");
    HashTable* hashTable = createHashTable();
    while (!feof(file))
    {
        char* buffer = calloc(100, sizeof(char));
        const int readBytes = fscanf(file, "%s", buffer);
        if (readBytes < 0)
        {
            break;
        }
        addToHashTable(hashTable, buffer);
    }
    fclose(file);
    return hashTable;
}

int main()
{
    HashTable* myTable = createHashTableFromFile("text.txt");
    printTableStatistics(myTable);
    return 0;
}
