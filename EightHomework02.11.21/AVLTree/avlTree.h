#pragma once
#include <stdbool.h>

// node of tree
typedef struct TreeNode TreeNode;

// root of tree
typedef struct TreeRoot TreeRoot;

// create empty TreeRoot
TreeRoot* createTreeRoot();

// removes the entire Tree
void deleteTree(TreeRoot** root);

// adds a new node to the tree or replaces the value
// if a node with this key exists
void addTreeNode(TreeRoot** root, int key, char* value);

// finds a value for a given key in the dictionary
char* findValue(TreeRoot* root, int key);

// checks if the given key is in the dictionary
bool isKeyInTree(TreeRoot* root, int key);

// Deletes the given key and its associated value from the dictionary
void removeEntry(TreeRoot** root, int key);