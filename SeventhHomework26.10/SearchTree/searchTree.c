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

Dictionary* createDictionary()
{
    return calloc(1, sizeof(Dictionary));
}

typedef enum Direction
{
    left,
    right
} Direction;

void transfer(TreeNode** node, Direction directionOfSon)
{
    if ((*node)->parent == NULL)
    {
        return;
    }
    if (directionOfSon == right)
    {
        (*node)->rightSon->parent = (*node)->parent;
    }
    else
    {
        (*node)->leftSon->parent = (*node)->parent;
    }
    if ((*node)->parent->rightSon == (*node))
    {
        if (directionOfSon == right)
        {
            (*node)->parent->rightSon = (*node)->rightSon;
            (*node)->rightSon = NULL;
            return;
        }
        (*node)->parent->rightSon = (*node)->leftSon;
        (*node)->leftSon = NULL;
    }
    else
    {
        if (directionOfSon == right)
        {
            (*node)->parent->leftSon = (*node)->rightSon;
            (*node)->rightSon = NULL;
            return;
        }
        (*node)->parent->leftSon = (*node)->leftSon;
        (*node)->leftSon = NULL;
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
    TreeNode** node = calloc(1, sizeof(TreeNode**));
    (*node) = dictionary->treeRoot;
    while (true)
    {
        if (key == (*node)->key)
        {
            free((*node)->value);
            (*node)->value = value;
            free(node);
            return;
        }
        if (key > (*node)->key)
        {
            if ((*node)->rightSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->parent = (*node);
                newNode->key = key;
                newNode->value = value;
                (*node)->rightSon = newNode;
                free(node);
                return;
            }
            (*node) = (*node)->rightSon;
        }
        else
        {
            if ((*node)->leftSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->parent = (*node);
                newNode->key = key;
                newNode->value = value;
                (*node)->leftSon = newNode;
                free(node);
                return;
            }
            (*node) = (*node)->leftSon;
        }
    }
}

void freeNode(Dictionary** root, TreeNode*** retrievableNode)
{
    if ((*root)->treeRoot == (**retrievableNode))
    {
        free((**retrievableNode)->value);
        free((*root)->treeRoot);
        free(*root);
        free(*retrievableNode);
        return;
    }
    if ((**retrievableNode)->parent != NULL)
    {
        if ((**retrievableNode)->parent->rightSon == (**retrievableNode))
        {
            (**retrievableNode)->parent->rightSon = NULL;
            free((**retrievableNode)->value);
            free(**retrievableNode);
            free(*retrievableNode);
            return;
        }
        (**retrievableNode)->parent->leftSon = NULL;
        free((**retrievableNode)->value);
        free(**retrievableNode);
        free(*retrievableNode);
    }
    else
    {
        free((**retrievableNode)->value);
        free(**retrievableNode);
        free(*retrievableNode);
    }
}


void removeTreeNode(Dictionary** root, TreeNode*** retrievableNode)
{
    if ((*root)->treeRoot == NULL)
    {
        return;
    }
    bool isRoot = (**retrievableNode) == (*root)->treeRoot;
    if ((**retrievableNode)->leftSon == NULL
        && (**retrievableNode)->rightSon == NULL)
    {
        freeNode(root, retrievableNode);
        return;
    }
    if ((**retrievableNode)->leftSon != NULL
        && (**retrievableNode)->rightSon == NULL)
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
    if ((**retrievableNode)->leftSon == NULL
        && (**retrievableNode)->rightSon != NULL)
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
    TreeNode** newNode = calloc(1, sizeof(TreeNode*));
    (*newNode) = (**retrievableNode)->leftSon;
    if ((*newNode)->rightSon == NULL)
    {
        (**retrievableNode)->key = (*newNode)->key;
        free((**retrievableNode)->value);
        (**retrievableNode)->value = (*newNode)->value;
        (*newNode)->parent->leftSon = (*newNode)->leftSon;
        if ((*newNode)->leftSon != NULL)
        {
            (*newNode)->leftSon->parent = (*newNode)->parent;
        }
        freeNode(root, &newNode);
        free(*retrievableNode);
    }
    while ((*newNode)->rightSon != NULL)
    {
        (*newNode) = (*newNode)->rightSon;
    }
    (**retrievableNode)->key = (*newNode)->key;
    free((**retrievableNode)->value);
    (**retrievableNode)->value = (*newNode)->value;
    (*newNode)->parent->rightSon = (*newNode)->leftSon;
    removeTreeNode(root, &newNode);
    free(*retrievableNode);
}

TreeNode** findNode(Dictionary* root, int key)
{
    if (root == NULL || root->treeRoot == NULL)
    {
        return NULL;
    }
    TreeNode** node = calloc(1, sizeof(TreeNode*));
    if (node == NULL)
    {
        return NULL;
    }
    (*node) = root->treeRoot;
    while (true)
    {
        if (key == (*node)->key)
        {
            return node;
        }
        if (key > (*node)->key)
        {
            if ((*node)->rightSon == NULL)
            {
                free(node);
                return NULL;
            }
            (*node) = (*node)->rightSon;
        }
        else
        {
            if ((*node)->leftSon == NULL)
            {
                free(node);
                return NULL;
            }
            (*node) = (*node)->leftSon;
        }
    }
}

char* findValue(Dictionary* dictionary, int key)
{
    TreeNode** node = findNode(dictionary, key);
    if (node == NULL)
    {
        return NULL;
    }
    char* value = (*node)->value;
    free(node);

    return value;
}

bool isKeyInDictionary(Dictionary* dictionary, int key)
{
    TreeNode** node = findNode(dictionary, key);
    if (node != NULL)
    {
        free(node);
        return true;
    }
    return false;
}

void removeEntry(Dictionary* dictionary, int key)
{
    TreeNode** node = findNode(dictionary, key);
    if (node != NULL)
    {
        removeTreeNode(&dictionary, &node);
    }
}