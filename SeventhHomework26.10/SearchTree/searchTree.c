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
    return NULL;
}

void deleteBranch(CurrentTreeNode** branch)
{
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
    free((*branch)->currentTreeNode->value);
    free((*branch)->currentTreeNode->leftSon);
    free((*branch)->currentTreeNode->rightSon);
    free((*branch)->currentTreeNode->parent);
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

char* removeTreeNode(CurrentTreeNode** retrievableNode)
{
    char* currentValue = (*retrievableNode)->currentTreeNode->value;
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
        (*retrievableNode)->currentTreeNode->leftSon->parent =
                (*retrievableNode)->currentTreeNode->parent;
        (*retrievableNode)->currentTreeNode->leftSon = NULL;
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

char* findValue(TreeRoot* root, int key)
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
            char* value = node->currentTreeNode->value;
            free(node);
            return value;
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

bool isKeyInTree(TreeRoot* root, int key)
{
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    if (node == NULL)
    {
        return false;
    }
    node->currentTreeNode = root->treeRoot;
    while (true)
    {
        if (key == node->currentTreeNode->key)
        {
            free(node);
            return true;
        }
        if (key > node->currentTreeNode->key)
        {
            if (node->currentTreeNode->rightSon == NULL)
            {
                free(node);
                return false;
            }
            node->currentTreeNode = node->currentTreeNode->rightSon;
        }
        else
        {
            if (node->currentTreeNode->leftSon == NULL)
            {
                free(node);
                return false;
            }
            node->currentTreeNode = node->currentTreeNode->leftSon;
        }
    }
}

// Deletes the given key and its associated value from the dictionary.
void removeEntry(TreeRoot** root, int key)
{

}