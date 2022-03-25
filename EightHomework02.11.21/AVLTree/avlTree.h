#pragma once
#include <stdbool.h>

// Dictionary structure
typedef struct Dictionary Dictionary;

// create empty Dictionary
Dictionary* createDictionary();

// removes the entire Dictionary
void deleteDictionary(Dictionary** dictionary);

// adds a new entry to the dictionary or replaces the value
// if a node with this key exists
// dictionary is not responsible for removing the pointer value
void addEntry(Dictionary* dictionary, const char* key, char* value);

// finds a value for a given key in the dictionary
char* findValue(Dictionary* dictionary, const char* key);

// checks if the given key is in the dictionary
bool isKeyInDictionary(Dictionary* dictionary, const char* key);

// Deletes the given key and its associated value from the dictionary
void removeEntry(Dictionary* dictionary, const char* key);

// technical function, never mind
// (returns tree height)
int getHeight(Dictionary* dictionary);