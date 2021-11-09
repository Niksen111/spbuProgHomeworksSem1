#include "searchTree.h"
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    char* value;
    TreeNode* parent;
    TreeNode* leftSon;
    TreeNode* rightSon;
} TreeNode;

typedef struct TreeRoot
{
    TreeNode* treeRoot;
} TreeRoot;

typedef struct CurrentTreeNode
{
    TreeNode* currentTreeNode;
} CurrentTreeNode;

TreeRoot* createTreeRoot()
{
    TreeRoot* newRoot = calloc(1, sizeof(TreeRoot));
    newRoot->treeRoot = NULL;
    return newRoot;
}

typedef enum Direction
{
    left,
    right
} Direction;

void attach(TreeNode* parent, TreeNode* child, Direction direction)
{
    if (direction == left)
    {
        parent->leftSon = child;
    }
    else
    {
        parent->rightSon = child;
    }
    if (child != NULL)
    {
    child->parent = parent;
    }
}

void deleteBranch(CurrentTreeNode** branch)
{
    if ((*branch)->currentTreeNode == NULL)
    {
        free(*branch);
        return;
    }
    if ((*branch)->currentTreeNode->leftSon != NULL)
    {
        CurrentTreeNode* leftSon = calloc(1, sizeof(CurrentTreeNode));
        leftSon->currentTreeNode = (*branch)->currentTreeNode->leftSon;
        deleteBranch(&leftSon);
    }
    if ((*branch)->currentTreeNode->rightSon != NULL)
    {
        CurrentTreeNode* rightSon = calloc(1, sizeof(CurrentTreeNode));
        rightSon->currentTreeNode = (*branch)->currentTreeNode->rightSon;
        deleteBranch(&rightSon);
    }
    free((*branch)->currentTreeNode);
    free(*branch);
}

void deleteTree(TreeRoot** root)
{
    CurrentTreeNode* removablePart = calloc(1, sizeof(CurrentTreeNode));
    removablePart->currentTreeNode = (*root)->treeRoot;
    deleteBranch(&removablePart);
    free(*root);
}

void addTreeNode(TreeRoot* root, int key, char* value)
{
    if (root->treeRoot == NULL)
    {
        root->treeRoot->key = key;
        root->treeRoot->value = value;
        return;
    }
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    node->currentTreeNode = root->treeRoot;
    while (true)
    {
        if (key == node->currentTreeNode->key)
        {
            free(node->currentTreeNode->value);
            node->currentTreeNode->value = value;
            free(node);
            return;
        }
        if (key > node->currentTreeNode->key)
        {
            if (node->currentTreeNode->rightSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->parent = node->currentTreeNode;
                newNode->key = key;
                newNode->value = value;
                free(node);
                return;
            }
            node->currentTreeNode = node->currentTreeNode->rightSon;
        }
        else
        {
            if (node->currentTreeNode->leftSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->parent = node->currentTreeNode;
                newNode->key = key;
                newNode->value = value;
                free(node);
                return;
            }
            node->currentTreeNode = node->currentTreeNode->leftSon;
        }
    }
}

bool isLeftSon(CurrentTreeNode* currentTreeNode)
{
    return currentTreeNode->currentTreeNode->parent->leftSon
        == currentTreeNode->currentTreeNode;
}

char* removeTreeNode(TreeRoot** root, CurrentTreeNode** retrievableNode)
{
    char* currentValue = (*retrievableNode)->currentTreeNode->value;
    bool isRoot = (*retrievableNode)->currentTreeNode == (*root)->treeRoot;
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
        && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        deleteBranch(retrievableNode);
        return currentValue;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon != NULL
        && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        if (isLeftSon(*retrievableNode))
        {
            (*retrievableNode)->currentTreeNode->parent->leftSon =
                    (*retrievableNode)->currentTreeNode->leftSon;
            (*retrievableNode)->currentTreeNode->leftSon->parent =
                    (*retrievableNode)->currentTreeNode->parent;
            (*retrievableNode)->currentTreeNode->leftSon = NULL;
            deleteBranch(retrievableNode);

            return currentValue;
        }
        (*retrievableNode)->currentTreeNode->parent->rightSon =
                (*retrievableNode)->currentTreeNode->leftSon;
        (*retrievableNode)->currentTreeNode->rightSon->parent =
                (*retrievableNode)->currentTreeNode->parent;
        (*retrievableNode)->currentTreeNode->rightSon = NULL;
        deleteBranch(retrievableNode);

        return currentValue;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
        && (*retrievableNode)->currentTreeNode->rightSon != NULL)
    {
        if (isLeftSon(*retrievableNode))
        {
            (*retrievableNode)->currentTreeNode->parent->leftSon =
                    (*retrievableNode)->currentTreeNode->rightSon;
            (*retrievableNode)->currentTreeNode->rightSon->parent =
                    (*retrievableNode)->currentTreeNode->parent;
            (*retrievableNode)->currentTreeNode->rightSon = NULL;
            deleteBranch(retrievableNode);

            return currentValue;
        }
        (*retrievableNode)->currentTreeNode->parent->rightSon =
                (*retrievableNode)->currentTreeNode->rightSon;
        (*retrievableNode)->currentTreeNode->rightSon->parent =
                (*retrievableNode)->currentTreeNode->parent;
        (*retrievableNode)->currentTreeNode->rightSon = NULL;
        deleteBranch(retrievableNode);

        return currentValue;
    }
    CurrentTreeNode* newNode = calloc(1, sizeof(CurrentTreeNode));
    newNode->currentTreeNode = (*retrievableNode)->currentTreeNode->leftSon;
    while (newNode->currentTreeNode->rightSon != NULL)
    {
        newNode->currentTreeNode = newNode->currentTreeNode->rightSon;
    }
    (*retrievableNode)->currentTreeNode->key = newNode->currentTreeNode->key;
    (*retrievableNode)->currentTreeNode->value = newNode->currentTreeNode->value;
    newNode->currentTreeNode->parent->rightSon = newNode->currentTreeNode->leftSon;
    if (newNode->currentTreeNode->leftSon != NULL)
    {
        newNode->currentTreeNode->leftSon = newNode->currentTreeNode->parent;
    }
    newNode->currentTreeNode->leftSon = NULL;
    deleteBranch(&newNode);

    return currentValue;
}

CurrentTreeNode* findNode(TreeRoot* root, int key)
{
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->currentTreeNode = root->treeRoot;
    while (true)
    {
        if (key == node->currentTreeNode->key)
        {
            return node;
        }
        if (key > node->currentTreeNode->key)
        {
            if (node->currentTreeNode->rightSon == NULL)
            {
                free(node);
                return NULL;
            }
            node->currentTreeNode = node->currentTreeNode->rightSon;
        }
        else
        {
            if (node->currentTreeNode->leftSon == NULL)
            {
                free(node);
                return NULL;
            }
            node->currentTreeNode = node->currentTreeNode->leftSon;
        }
    }
}

char* findValue(TreeRoot* root, int key)
{
    CurrentTreeNode* node = findNode(root, key);
    if (node == NULL)
    {
        return NULL;
    }
    char* value = node->currentTreeNode->value;
    free(node);

    return value;
}

bool isKeyInTree(TreeRoot* root, int key)
{
    CurrentTreeNode* node = findNode(root, key);
    if (node != NULL)
    {
        free(node);
        return true;
    }
    return false;
}

void removeEntry(TreeRoot** root, int key)
{

    CurrentTreeNode* node = findNode(*root, key);
    if (node != NULL)
    {
        removeTreeNode(root, &node);
    }
}