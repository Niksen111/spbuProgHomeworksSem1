#include "hashTable.h"
#include "list.h"
#include <string.h>

typedef struct HashTable
{
    Position* hashTable[100000];
} HashTable;

int calculateHashFunction(char* string)
{
    int result = 0;
    int length =
}

void addToHashTable(HashTable* hashTable, char* string)
{

}

void printHashTable(HashTable* hashTable);