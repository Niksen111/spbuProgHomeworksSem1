#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parseTree.h"

typedef struct TreeNode
{
    char value;
    struct TreeNode* leftSon;
    struct TreeNode* rightSon;
    struct TreeNode* parent;
} TreeNode;

typedef struct ParseTree
{
    TreeNode* root;
} ParseTree;

int operation(const int value1, const int value2,
        const int operation, int* errorCode)
{
    *errorCode = 0;
    switch (operation)
    {
    case (int) '+':
        return value1 + value2;
    case (int) '-':
        return value1 - value2;
    case (int) '*':
        return value1 * value2;
    case (int) '/':
        if (value2 == 0)
        {
            *errorCode = -1;
            return 0;
        }
        return value1 / value2;
    default:
        *errorCode = -2;
        return 0;
    }
}

bool inLine(const char string[], const char symbol)
{
    for (int i = 0; string[i] != '\0'; ++i)
    {
        if (string[i] == symbol)
        {
            return true;
        }
    }
    return false;
}

int add(ParseTree** tree, ParseTree* root, char value)
{
    TreeNode* newNode = calloc(1, sizeof(TreeNode));
    if (newNode == NULL)
    {
        return -1;
    }
    bool isDigit = value >= '0' && value <= '9';
    newNode->value = value;
    if ((*tree)->root == NULL)
    {
        root->root = newNode;
        (*tree)->root = newNode;
        return 0;
    }
    if ((*tree)->root->leftSon == NULL)
    {
        newNode->parent = (*tree)->root;
        (*tree)->root->leftSon = newNode;
        if (!isDigit)
        {
            (*tree)->root = (*tree)->root->leftSon;
        }
        return 0;
    }
    if ((*tree)->root->rightSon == NULL)
    {
        newNode->parent = (*tree)->root;
        (*tree)->root->rightSon = newNode;
        if (!isDigit)
        {
            (*tree)->root = (*tree)->root->rightSon;
        }
        else
        {
            while((*tree)->root != root->root && (*tree)->root->rightSon != NULL)
            {
                (*tree)->root = (*tree)->root->parent;
            }
        }
        return 0;
    }
    return -2;
}

void deleteTreeRecursive(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTreeRecursive(root->leftSon);
    deleteTreeRecursive(root->rightSon);
    free(root);
}

void deleteTree(ParseTree** root)
{
    deleteTreeRecursive((*root)->root);
    *root = NULL;
}

ParseTree* createTree(const char expression[], int *errorCode)
{
    *errorCode = 0;
    ParseTree* root = calloc(1, sizeof(ParseTree));
    if (root == NULL)
    {
        *errorCode = -1;
        return NULL;
    }
    ParseTree* currentNode = calloc(1, sizeof(ParseTree));
    if (currentNode == NULL)
    {
        *errorCode = -1;
        free(root);
        return NULL;
    }
    const char operations[5] = { '+', '-', '*', '/' };
    const unsigned long lengthOfExpression = strlen(expression);
    for (unsigned long i = 0; i < lengthOfExpression; ++i)
    {
        if (inLine(operations, expression[i]) || expression[i] >= '0' && expression[i] <= '9')
        {
            *errorCode = add(&currentNode, root, expression[i]);
            if (*errorCode != 0)
            {
                deleteTree(&root);
                free(root);
                free(currentNode);
                return NULL;
            }
        }
    }
    free(currentNode);
    return root;
}

int calculateValueOfTree(ParseTree* root)
{
    if (root->root->value < '0' || root->root->value > '9')
    {
        ParseTree* leftTree = calloc(1, sizeof(ParseTree));
        ParseTree* rightTree = calloc(1, sizeof(ParseTree));
        leftTree->root = root->root->leftSon;
        rightTree->root = root->root->rightSon;
        int leftValue = calculateValueOfTree(leftTree);
        int rightValue = calculateValueOfTree(rightTree);
        int errorCode = 0;
        int result = operation(leftValue, rightValue, root->root->value, &errorCode);
        if (errorCode != 0)
        {
            return -1;
        }
        free(leftTree);
        free(rightTree);
        return result;
    }
    return (root->root->value) - '0';
}

void printTree(ParseTree* root)
{
    if (root->root->value < '0' || root->root->value > '9')
    {
        printf("( %c ", (root->root->value));
        ParseTree* leftTree = calloc(1, sizeof(ParseTree));
        ParseTree* rightTree = calloc(1, sizeof(ParseTree));
        leftTree->root = root->root->leftSon;
        rightTree->root = root->root->rightSon;
        printTree(leftTree);
        printTree(rightTree);
        printf(") ");
        free(leftTree);
        free(rightTree);
        return;
    }
    printf("%c ", (root->root->value));
}