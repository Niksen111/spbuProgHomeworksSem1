#pragma once

// HashTable structure
typedef struct HashTable HashTable;

// creates HashTable
HashTable* createHashTable(int tableSize);

// adds string to the hashTable
void addToHashTable(HashTable* hashTable, char* line, int numberOfTheLines);

// recalculates the number of voids, the length of all lists and
// the length of the maximum list of the hash table.
void recalculateTableStatistics(HashTable* hashTable);

// prints table statistics
void printTableStatistics(HashTable* hashTable);

// returns the number of repetitions of the word in the text
int giveNumberOfRepetitionsOfWord(HashTable* table, char* word);

// deletes HashTable
void deleteHashTable(HashTable* hashTable);

// redesigns the table to the "optimal size"
void redoHashTable(HashTable** hashTable);

// prints all the words from the hash table
void printHashTable(HashTable* hashTable);

// creates a hash table based on this file
HashTable* createHashTableFromFile(char name[]);