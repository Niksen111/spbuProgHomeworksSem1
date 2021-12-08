#include <stdio.h>
#include <stdlib.h>
#include "hashTable.h"
#include "hashTableTests.h"

int main()
{
    if (!testHashTable())
    {
        printf("Tests failed(\n");
        return -1;
    }
    HashTable* myTable = createHashTableFromFile("test.txt");
    printTableStatistics(myTable);
    deleteHashTable(&myTable);
    return 0;
}
