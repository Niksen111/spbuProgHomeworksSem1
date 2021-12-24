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

void fillWithZeros(char* line, int lineSize)
{
    for (int i = 0; i < lineSize; ++i)
    {
        line[i] = 0;
    }
}

bool isNumber(const char* line)
{
    return line[0] > '0' && line[0] < '9' || line[1] > '0' && line[1] < '9';
}

int convertToInt(const char* number)
{
    int result = 0;
    int start = number[0] == '-' ? 1 : 0;
    for (int i = start; number[i] != '\0'; ++i)
    {
        result = result * 10 + (int)(number[i] - '0');
    }
    return start == 1 ? result * (-1) : result;
}

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
    deleteTreeRecursive(root->rightSon);
    free(root->value);
    free(root);
}

void deleteTree(ParseTree** root)
{
    if ((*root) == NULL)
    {
        return;
    }
    deleteTreeRecursive((*root)->root);
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
    newNode->value = calloc(strlen(value) + 1, sizeof(char));
    strcat(newNode->value, value);
    bool isDigit = value[0] >= '0' && value[0] <= '9'
            || value[1] >= '0' && value[1] <= '9';
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
    char currentValue[15] = { 0 };
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
                    currentValue[j] = c;
                    ++j;
                    break;
                }
                if (inLine(operations, c))
                {
                    state = 0;
                    currentValue[j] = c;
                    j = 0;
                    add(root, currentNode, currentValue);
                    fillWithZeros(currentValue, 15);
                    break;
                }
                if (c >= '0' && c <= '9')
                {
                    state = 2;
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
                fillWithZeros(currentValue, 15);
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
                fillWithZeros(currentValue, 15);
                break;
            }
        }
    }
    free(currentNode);
    return root;
}

int calculateValueOfTreeRecursive(TreeNode* node)
{
    if (isNumber(node->value))
    {
        return convertToInt(node->value);
    }
    TreeNode* leftSon = node->leftSon;
    TreeNode* rightSon = node->rightSon;
    int leftValue = calculateValueOfTreeRecursive(leftSon);
    int rightValue = calculateValueOfTreeRecursive(rightSon);
    int errorCode = 0;
    int result = operation(leftValue, rightValue, node->value[0], &errorCode);
    if (errorCode != 0)
    {
        return -1;
    }
    return result;
}

int calculateValueOfTree(ParseTree* root)
{
    return calculateValueOfTreeRecursive(root->root);
}

void printTreeRecursive(TreeNode* node)
{
    if (isNumber(node->value))
    {
        printf("%s ", node->value);
        return;
    }
    printf("( %s ", node->value);
    TreeNode* leftSon = node->leftSon;
    TreeNode* rightSon = node->rightSon;
    printTreeRecursive(leftSon);
    printTreeRecursive(rightSon);
    printf(") ");
}

void printTree(ParseTree* root)
{
    printTreeRecursive(root->root);
}