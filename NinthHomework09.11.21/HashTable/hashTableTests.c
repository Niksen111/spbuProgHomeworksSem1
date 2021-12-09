#include "hashTableTests.h"
#include "hashTable.h"
#include "listTests.h"
#include <stdlib.h>

bool testCreateHashTable()
{
    HashTable* hashTable = createHashTable(35);
    addToHashTable(hashTable, "Dog", 5);
    addToHashTable(hashTable, "Cat", 10);
    bool result = giveNumberOfRepetitionsOfWord(hashTable, "Dog") == 5
            && giveNumberOfRepetitionsOfWord(hashTable, "Cat") == 10;
    deleteHashTable(&hashTable);

    return result;
}

bool testAddToHashTable()
{
    HashTable* hashTable = createHashTable(35);
    addToHashTable(hashTable, "Dog", 5);
    addToHashTable(hashTable, "Cat", 10);
    bool result = giveNumberOfRepetitionsOfWord(hashTable, "Dog") == 5
            && giveNumberOfRepetitionsOfWord(hashTable, "Cat") == 10;
    deleteHashTable(&hashTable);

    return result;
}

bool testGiveNumberOfRepetitionsOfWord()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    bool result = giveNumberOfRepetitionsOfWord(hashTable, "hello") == 3
            && giveNumberOfRepetitionsOfWord(hashTable, "mama") == 1
            && giveNumberOfRepetitionsOfWord(hashTable, "ABCD") == -1;
    deleteHashTable(&hashTable);
    return result;
}

bool testDeleteHashTable()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    bool result = giveNumberOfRepetitionsOfWord(hashTable, "hello") == 3;
    deleteHashTable(&hashTable);
    result = result && giveNumberOfRepetitionsOfWord(hashTable, "hello") == -1
            && hashTable == NULL;

    return result;
}

bool testRedoHashTable()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    bool result = giveHashTableSize(hashTable) == 7;
    addToHashTable(hashTable, "123", 5);
    addToHashTable(hashTable, "Size", 5);
    recalculateTableStatistics(hashTable);
    redoHashTable(&hashTable);
    result = result && giveHashTableSize(hashTable) == 11;
    deleteHashTable(&hashTable);

    return result;
}

bool testGiveHashTableSize()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    bool result = giveHashTableSize(hashTable) == 7;
    addToHashTable(hashTable, "123", 5);
    addToHashTable(hashTable, "Size", 5);
    recalculateTableStatistics(hashTable);
    redoHashTable(&hashTable);
    result = result && giveHashTableSize(hashTable) == 11;
    deleteHashTable(&hashTable);

    return result;
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

bool testHashTable(void)
{
    return testCreateHashTable() && testAddToHashTable()
        && testGiveNumberOfRepetitionsOfWord()
        && testDeleteHashTable() && testRedoHashTable()
        && testCreateHashTableFromFile() && testGiveHashTableSize()
        && testList();
}