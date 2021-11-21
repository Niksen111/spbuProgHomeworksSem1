#include "avlTree.h"
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
    return calloc(1, sizeof(TreeRoot));
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
    deleteBranchRecursive(branch->rightSon);
    free(branch);
}

void deleteBranch(CurrentTreeNode** branch)
{
    if ((*branch) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*branch)->currentTreeNode);
    (*branch) = NULL;
}

void deleteTree(TreeRoot** root)
{
    if ((*root) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*root)->treeRoot);
    (*root) = NULL;
}

void addTreeNode(TreeRoot** root, int key, char* value)
{
    if ((*root)->treeRoot == NULL)
    {
        TreeNode* newTreeNode = calloc(1, sizeof(TreeNode));
        newTreeNode->key = key;
        newTreeNode->value = value;
        (*root)->treeRoot = newTreeNode;
        return;
    }
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    node->currentTreeNode = (*root)->treeRoot;
    while (true)
    {
        if (key == node->currentTreeNode->key)
        {
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

void freeNode(TreeRoot** root, CurrentTreeNode** retrievableNode)
{
    if ((*root)->treeRoot == (*retrievableNode)->currentTreeNode)
    {
        free((*root)->treeRoot);
        (*root) = NULL;
        (*retrievableNode) = NULL;
        return;
    }
    if ((*retrievableNode)->currentTreeNode->parent != NULL)
    {
        if ((*retrievableNode)->currentTreeNode->parent->rightSon == (*retrievableNode)->currentTreeNode)
        {
            (*retrievableNode)->currentTreeNode->parent->rightSon = NULL;
            free((*retrievableNode)->currentTreeNode);
            return;
        }
        (*retrievableNode)->currentTreeNode->parent->leftSon = NULL;
        free((*retrievableNode)->currentTreeNode);
    }
}


void removeTreeNode(TreeRoot** root, CurrentTreeNode** retrievableNode)
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
        if (isRoot)
        {
            deleteTree(root);
        }
        return ;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon != NULL
            && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        freeNode(root, retrievableNode);
        if (isRoot)
        {
            deleteTree(root);
        }
        return;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
            && (*retrievableNode)->currentTreeNode->rightSon != NULL)
    {
        transfer((*retrievableNode), left);
        freeNode(root, retrievableNode);
        if (isRoot)
        {
            deleteTree(root);
        }
        return;
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
    removeTreeNode(root, &newNode);
}

CurrentTreeNode* findNode(TreeRoot* root, int key)
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
    CurrentTreeNode* node = findNode((*root), key);
    if (node != NULL)
    {
        removeTreeNode(root, &node);
    }
} 