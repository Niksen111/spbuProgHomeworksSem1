#pragma once

typedef struct ParseTree ParseTree;

// creates a parse tree by the expression
ParseTree* createTree(const char* expression);

// calculates value of the ParseTree
int calculateValueOfTree(ParseTree* root);

// prints the value of the tree
void printTree(ParseTree* root);