#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parseTree.h"

typedef struct TreeNode
{
    char* value;
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

void deleteTreeRecursive(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    deleteTreeRecursive(root->leftSon);
    free(root->leftSon);
    deleteTreeRecursive(root->rightSon);
    free(root->rightSon);
}

void deleteTree(ParseTree** root)
{
    if ((*root) == NULL)
    {
        return;
    }
    deleteTreeRecursive((*root)->root);
    free((*root)->root);
    free(*root);
    (*root) = NULL;
}

int add(ParseTree* root, TreeNode** currentNode, char* value)
{
    TreeNode* newNode = calloc(1, sizeof(TreeNode));
    if (newNode == NULL)
    {
        return -1;
    }
    bool isDigit = value[0] >= '0' && value[0] <= '9'
            || value[1] >= '0' && value[1] <= '9';
    newNode->value = value;
    if (*currentNode == NULL)
    {
        root->root = newNode;
        *currentNode = newNode;
        return 0;
    }
    if ((*currentNode)->leftSon == NULL)
    {
        newNode->parent = *currentNode;
        (*currentNode)->leftSon = newNode;
        if (!isDigit)
        {
            *currentNode = (*currentNode)->leftSon;
        }
        return 0;
    }
    if ((*currentNode)->rightSon == NULL)
    {
        newNode->parent = *currentNode;
        (*currentNode)->rightSon = newNode;
        if (!isDigit)
        {
            *currentNode = (*currentNode)->rightSon;
        }
        else
        {
            while(*currentNode != root->root && (*currentNode)->rightSon != NULL)
            {
                *currentNode = (*currentNode)->parent;
            }
        }
        return 0;
    }
    return -2;
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
    TreeNode** currentNode = calloc(1, sizeof(TreeNode*));
    if (currentNode == NULL)
    {
        *errorCode = -1;
        free(root);
        return NULL;
    }
    const char* operations = "*/+-";
    const int lengthOfExpression = strlen(expression);
    int state = 0;
    char* currentValue = NULL;
    int j = 0;
    for (int i = 0; i < lengthOfExpression; ++i)
    {
        char c = expression[i];
        switch (state)
        {
            case 0:
            {
                if (c == '-')
                {
                    state = 1;
                    currentValue = calloc(15, sizeof(char));
                    currentValue[j] = c;
                    ++j;
                    break;
                }
                if (inLine(operations, c))
                {
                    state = 0;
                    currentValue = calloc(2, sizeof(char));
                    currentValue[j] = c;
                    j = 0;
                    add(root, currentNode, currentValue);
                    currentValue = NULL;
                    break;
                }
                if (c >= '0' && c <= '9')
                {
                    state = 2;
                    currentValue = calloc(15, sizeof(char));
                    currentValue[j] = c;
                    ++j;
                    break;
                }
                break;
            }
            case 1:
            {
                if (c >= '0' && c <= '9')
                {
                    state = 2;
                    currentValue[j] = c;
                    ++j;
                    break;
                }
                state = 0;
                j = 0;
                add(root, currentNode, currentValue);
                currentValue = NULL;
                break;
            }
            case 2:
            {
                if (c >= '0' && c <= '9')
                {
                    state = 2;
                    currentValue[j] = c;
                    ++j;
                    break;
                }
                state = 0;
                j = 0;
                add(root, currentNode, currentValue);
                currentValue = NULL;
                break;
            }
        }
    }
    free(currentNode);
    return root;
}

int calculateValueOfTree(ParseTree* root)
{
    if (root->root->value > '0' && root->root->value < '9')
    {
        return (root->root->value) - '0';
    }
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
        free(leftTree);
        free(rightTree);
        return -1;
    }
    free(leftTree);
    free(rightTree);
    return result;
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