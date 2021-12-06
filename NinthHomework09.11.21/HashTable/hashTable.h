#pragma once

typedef struct HashTable HashTable;

void addToHashTable(HashTable* hashTable, char* string);

void printHashTable(HashTable* hashTable);