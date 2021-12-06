#pragma once

// HashTable structure
typedef struct HashTable HashTable;

// creates HashTable
HashTable* createHashTable();

// adds string to the hashTable
void addToHashTable(HashTable* hashTable, char* string);

// prints table statistics
void printTableStatistics(HashTable* hashTable);

// deletes HashTable
void deleteHashTable(HashTable** hashTable);

// prints all the words from the hash table
void printHashTable(HashTable* hashTable);