#include "hashTableTests.h"
#include "hashTable.h"
#include "listTests.h"

bool testCreateHashTable()
{
    HashTable* hashTable = createHashTable(35);
    addToHashTable(hashTable, "Dog", 5);
    addToHashTable(hashTable, "Cat", 10);
    bool result = giveNumberOfRepetitionsOfWord(hashTable, "Dog") == 5
            && giveNumberOfRepetitionsOfWord(hashTable, "Cat") == 10;
    deleteHashTable(hashTable);

    return result;
}

bool testAddToHashTable()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    return true;
}

bool testRecalculateTableStatistics()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    return true;
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
    return true;
}

bool testRedoHashTable()
{
    HashTable* hashTable = createHashTableFromFile("file.txt");
    return true;
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
        && testRecalculateTableStatistics()
        && testGiveNumberOfRepetitionsOfWord()
        && testDeleteHashTable() && testRedoHashTable()
        && testCreateHashTableFromFile() && testList();
}