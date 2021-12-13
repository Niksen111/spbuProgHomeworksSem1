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
// dictionary is responsible for removing the pointer value
void addEntry(Dictionary* dictionary, int key, char* value);

// finds a value for a given key in the dictionary
char* findValue(Dictionary* dictionary, int key);

// checks if the given key is in the dictionary
bool isKeyInDictionary(Dictionary* dictionary, int key);

// Deletes the given key and its associated value from the dictionary
void removeEntry(Dictionary** dictionary, int key);

// technical function, never mind
// (returns tree height)
int getHeight(Dictionary* dictionary);