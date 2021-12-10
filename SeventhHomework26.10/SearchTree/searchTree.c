#include "searchTree.h"
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    char* value;
    struct TreeNode* parent;
    struct TreeNode* leftSon;
    struct TreeNode* rightSon;
} TreeNode;

typedef struct Dictionary
{
    TreeNode* treeRoot;
} Dictionary;

typedef struct CurrentTreeNode
{
    TreeNode* currentTreeNode;
} CurrentTreeNode;

Dictionary* createDictionary()
{
    return calloc(1, sizeof(Dictionary));
}

typedef enum Direction
{
    left,
    right
} Direction;

void transfer(CurrentTreeNode* node, Direction directionOfSon)
{
    if (node->currentTreeNode->parent == NULL)
    {
        return;
    }
    if (directionOfSon == right)
    {
        node->currentTreeNode->rightSon->parent = node->currentTreeNode->parent;
    }
    else
    {
        node->currentTreeNode->leftSon->parent = node->currentTreeNode->parent;
    }
    if (node->currentTreeNode->parent->rightSon == node->currentTreeNode)
    {
        if (directionOfSon == right)
        {
            node->currentTreeNode->parent->rightSon = node->currentTreeNode->rightSon;
            node->currentTreeNode->rightSon = NULL;
            return;
        }
        node->currentTreeNode->parent->rightSon = node->currentTreeNode->leftSon;
        node->currentTreeNode->leftSon = NULL;
    }
    else
    {
        if (directionOfSon == right)
        {
            node->currentTreeNode->parent->leftSon = node->currentTreeNode->rightSon;
            node->currentTreeNode->rightSon = NULL;
            return;
        }
        node->currentTreeNode->parent->leftSon = node->currentTreeNode->leftSon;
        node->currentTreeNode->leftSon = NULL;
    }
}

void deleteBranchRecursive(TreeNode* branch)
{
    if (branch == NULL)
    {
        return;
    }
    deleteBranchRecursive(branch->leftSon);
    free(branch->leftSon);
    deleteBranchRecursive(branch->rightSon);
    free(branch->rightSon);
    free(branch->value);
}

void deleteBranch(CurrentTreeNode** branch)
{
    if ((*branch) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*branch)->currentTreeNode);
    free((*branch)->currentTreeNode);
    free(*branch);
    (*branch) = NULL;
}

void deleteDictionary(Dictionary** dictionary)
{
    if ((*dictionary) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*dictionary)->treeRoot);
    free((*dictionary)->treeRoot);
    free(*dictionary);
    (*dictionary) = NULL;
}

void addEntry(Dictionary* dictionary, int key, char* value)
{
    if (dictionary->treeRoot == NULL)
    {
        TreeNode* newTreeNode = calloc(1, sizeof(TreeNode));
        newTreeNode->key = key;
        newTreeNode->value = value;
        dictionary->treeRoot = newTreeNode;
        return;
    }
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    node->currentTreeNode = dictionary->treeRoot;
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
                node->currentTreeNode->rightSon = newNode;
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
                node->currentTreeNode->leftSon = newNode;
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

void freeNode(Dictionary** root, CurrentTreeNode** retrievableNode)
{
    if ((*root)->treeRoot == (*retrievableNode)->currentTreeNode)
    {
        free((*retrievableNode)->currentTreeNode->value);
        free((*root)->treeRoot);
        free(*root);
        free(*retrievableNode);
        return;
    }
    if ((*retrievableNode)->currentTreeNode->parent != NULL)
    {
        if ((*retrievableNode)->currentTreeNode->parent->rightSon == (*retrievableNode)->currentTreeNode)
        {
            (*retrievableNode)->currentTreeNode->parent->rightSon = NULL;
            free((*retrievableNode)->currentTreeNode->value);
            free((*retrievableNode)->currentTreeNode);
            free(*retrievableNode);
            return;
        }
        (*retrievableNode)->currentTreeNode->parent->leftSon = NULL;
        free((*retrievableNode)->currentTreeNode->value);
        free((*retrievableNode)->currentTreeNode);
        free(*retrievableNode);
    }
    else
    {
        free((*retrievableNode)->currentTreeNode->value);
        free((*retrievableNode)->currentTreeNode);
        free(*retrievableNode);
    }
}


void removeTreeNode(Dictionary** root, CurrentTreeNode** retrievableNode)
{
    if ((*root)->treeRoot == NULL)
    {
        return;
    }
    bool isRoot = (*retrievableNode)->currentTreeNode == (*root)->treeRoot;
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
        && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        freeNode(root, retrievableNode);
        return;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon != NULL
        && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        transfer((*retrievableNode), left);
        if (isRoot)
        {
            (*root)->treeRoot = (*root)->treeRoot->leftSon;
            (*root)->treeRoot->parent = NULL;
        }
        freeNode(root, retrievableNode);
        return;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
        && (*retrievableNode)->currentTreeNode->rightSon != NULL)
    {
        transfer((*retrievableNode), right);
        if (isRoot)
        {
            (*root)->treeRoot = (*root)->treeRoot->rightSon;
            (*root)->treeRoot->parent = NULL;
        }
        freeNode(root, retrievableNode);
        return;
    }
    CurrentTreeNode* newNode = calloc(1, sizeof(CurrentTreeNode));
    newNode->currentTreeNode = (*retrievableNode)->currentTreeNode->leftSon;
    if (newNode->currentTreeNode->rightSon == NULL)
    {
        (*retrievableNode)->currentTreeNode->key = newNode->currentTreeNode->key;
        free((*retrievableNode)->currentTreeNode->value);
        (*retrievableNode)->currentTreeNode->value = newNode->currentTreeNode->value;
        newNode->currentTreeNode->parent->leftSon = newNode->currentTreeNode->leftSon;
        if (newNode->currentTreeNode->leftSon != NULL)
        {
            newNode->currentTreeNode->leftSon->parent = newNode->currentTreeNode->parent;
        }
        freeNode(root, &newNode);
        free(*retrievableNode);
    }
    while (newNode->currentTreeNode->rightSon != NULL)
    {
        newNode->currentTreeNode = newNode->currentTreeNode->rightSon;
    }
    (*retrievableNode)->currentTreeNode->key = newNode->currentTreeNode->key;
    free((*retrievableNode)->currentTreeNode->value);
    (*retrievableNode)->currentTreeNode->value = newNode->currentTreeNode->value;
    newNode->currentTreeNode->parent->rightSon = newNode->currentTreeNode->leftSon;
    removeTreeNode(root, &newNode);
    free(*retrievableNode);
}

CurrentTreeNode* findNode(Dictionary* root, int key)
{
    if (root == NULL || root->treeRoot == NULL)
    {
        return NULL;
    }
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

char* findValue(Dictionary* dictionary, int key)
{
    CurrentTreeNode* node = findNode(dictionary, key);
    if (node == NULL)
    {
        return NULL;
    }
    char* value = node->currentTreeNode->value;
    free(node);

    return value;
}

bool isKeyInDictionary(Dictionary* dictionary, int key)
{
    CurrentTreeNode* node = findNode(dictionary, key);
    if (node != NULL)
    {
        free(node);
        return true;
    }
    return false;
}

void removeEntry(Dictionary* dictionary, int key)
{
    CurrentTreeNode* node = findNode(dictionary, key);
    if (node != NULL)
    {
        removeTreeNode(&dictionary, &node);
    }
}