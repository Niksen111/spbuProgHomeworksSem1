#include "hashTableTests.h"
#include "hashTable.h"

HashTable* testCreateHashTable(int tableSize);

void testAddToHashTable(HashTable* hashTable, char* line, int numberOfTheLines);

void testRecalculateTableStatistics(HashTable* hashTable);

int testGiveNumberOfRepetitionsOfWord(HashTable* table, char* word);

void testDeleteHashTable(HashTable** hashTable);

void testRedoHashTable(HashTable** hashTable);