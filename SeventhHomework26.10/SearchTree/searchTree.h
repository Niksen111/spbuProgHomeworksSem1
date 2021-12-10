#pragma once
#include <stdbool.h>

// root of tree
typedef struct Dictionary Dictionary;

// create empty TreeRoot
Dictionary* createDictionary();

// removes the entire Tree
void deleteDictionary(Dictionary** dictionary);

// adds a new node to the tree or replaces the value
// if a node with this key exists
// dictionary is responsible for removing the pointer value
void addEntry(Dictionary* dictionary, int key, char* value);

// finds a value for a given key in the dictionary
char* findValue(Dictionary* dictionary, int key);

// checks if the given key is in the dictionary
bool isKeyInDictionary(Dictionary* dictionary, int key);

// Deletes the given key and its associated value from the dictionary
void removeEntry(Dictionary* dictionary, int key);