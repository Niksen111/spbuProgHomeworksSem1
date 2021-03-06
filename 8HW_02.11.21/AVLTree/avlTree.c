#include "avlTree.h"
#include <stdlib.h>
#include <string.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode
{
    const char* key;
    char* value;
    char height;
    struct TreeNode* parent;
    struct TreeNode* leftSon;
    struct TreeNode* rightSon;
} TreeNode;

typedef struct Dictionary
{
    TreeNode* AVLTreeRoot;
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

char calculateHeightDifference(TreeNode* node)
{
    if (node->rightSon != NULL && node->leftSon != NULL)
    {
        return node->rightSon->height - node->leftSon->height;
    }
    if (node->rightSon != NULL)
    {
        return node->rightSon->height + 1;
    }
    if (node->leftSon != NULL)
    {
        return -node->leftSon->height - 1;
    }
    return 0;
}

char calculateNodeHight(TreeNode* node)
{
    if (node->rightSon == NULL && node->leftSon == NULL)
    {
        return 0;
    }
    if (node->rightSon == NULL)
    {
        return node->leftSon->height + 1;
    }
    if (node->leftSon == NULL)
    {
        return node->rightSon->height + 1;
    }
    return max(node->leftSon->height, node->rightSon->height) + 1;
}

void fixHeight(TreeNode* node)
{
    node->height = calculateNodeHight(node);
    TreeNode* currentNode = node;
    while (currentNode->parent != NULL)
    {
        currentNode = currentNode->parent;
        char height = calculateNodeHight(currentNode);
        if (height == currentNode->height)
        {
            return;
        }
        currentNode->height = height;
    }
}

void smallLeftRotation(Dictionary* dictionary, TreeNode* node)
{
    if (dictionary->AVLTreeRoot == node)
    {
        dictionary->AVLTreeRoot = node->rightSon;
    }
    if (node->parent != NULL)
    {
        if (node->parent->rightSon == node)
        {
            node->parent->rightSon = node->rightSon;
        }
        else
        {
            node->parent->leftSon = node->rightSon;
        }
        node->rightSon->parent = node->parent;
    }
    else
    {
        node->rightSon->parent = NULL;
    }
    if (node->rightSon->leftSon != NULL)
    {
        node->rightSon->leftSon->parent = node;
    }
    node->parent = node->rightSon;
    node->rightSon = node->rightSon->leftSon;
    node->parent->leftSon = node;
    node->height = node->parent->rightSon->height;
}

void smallRightRotation(Dictionary* dictionary, TreeNode* node)
{
    if (dictionary->AVLTreeRoot == node)
    {
        dictionary->AVLTreeRoot = node->leftSon;
    }
    if (node->parent != NULL)
    {
        if (node->parent->rightSon == node)
        {
            node->parent->rightSon = node->leftSon;
        }
        else
        {
            node->parent->leftSon = node->leftSon;
        }
        node->leftSon->parent = node->parent;
    }
    else
    {
        node->leftSon->parent = NULL;
    }
    if (node->leftSon->rightSon != NULL)
    {
        node->leftSon->rightSon->parent = node;
    }
    node->parent = node->leftSon;
    node->leftSon = node->leftSon->rightSon;
    node->parent->rightSon = node;
    node->height = node->parent->leftSon->height;
}

void bigLeftRotation(Dictionary* dictionary, TreeNode* node)
{
    if (dictionary->AVLTreeRoot == node)
    {
        dictionary->AVLTreeRoot = node->rightSon->leftSon;
    }
    if (node->parent != NULL)
    {
        if (node->parent->rightSon == node)
        {
            node->parent->rightSon = node->rightSon->leftSon;
        }
        else
        {
            node->parent->leftSon = node->rightSon->leftSon;
        }
        node->rightSon->leftSon->parent = node->parent;
    }
    else
    {
        node->rightSon->leftSon->parent = NULL;
    }
    if (node->rightSon->leftSon->leftSon != NULL)
    {
        node->rightSon->leftSon->leftSon->parent = node;
    }
    if (node->rightSon->leftSon->rightSon != NULL)
    {
        node->rightSon->leftSon->rightSon->parent = node->rightSon;
    }
    node->parent = node->rightSon->leftSon;
    node->rightSon->leftSon = node->rightSon->leftSon->rightSon;
    node->rightSon->parent = node->rightSon->leftSon;
    node->parent->rightSon = node->rightSon;
    node->rightSon = node->parent->leftSon;
    node->parent->leftSon = node;
    node->height = node->parent->height;
    node->parent->height += 1;
    node->parent->rightSon->height = node->height;
}

void bigRightRotation(Dictionary* dictionary, TreeNode* node)
{
    if (dictionary->AVLTreeRoot == node)
    {
        dictionary->AVLTreeRoot = node->leftSon->rightSon;
    }
    if (node->parent != NULL)
    {
        if (node->parent->rightSon == node)
        {
            node->parent->rightSon = node->leftSon->rightSon;
        }
        else
        {
            node->parent->leftSon = node->leftSon->rightSon;
        }
        node->leftSon->rightSon->parent = node->parent;
    }
    else
    {
        node->leftSon->rightSon->parent = NULL;
    }
    if (node->leftSon->rightSon->rightSon != NULL)
    {
        node->leftSon->rightSon->rightSon->parent = node;
    }
    if (node->leftSon->rightSon->leftSon != NULL)
    {
        node->leftSon->rightSon->leftSon->parent = node->leftSon;
    }
    node->parent = node->leftSon->rightSon;
    node->leftSon->rightSon = node->leftSon->rightSon->leftSon;
    node->leftSon->parent = node->leftSon->rightSon;
    node->parent->leftSon = node->leftSon;
    node->leftSon = node->parent->rightSon;
    node->parent->rightSon = node;
    node->height = node->parent->height;
    node->parent->height += 1;
    node->parent->leftSon->height = node->height;
}

void rebalanceNode(Dictionary* dictionary, TreeNode* node)
{
    char heightDifference = calculateHeightDifference(node);
    if (heightDifference == 0)
    {
        return;
    }
    if (heightDifference > 0)
    {
        if (calculateHeightDifference(node->rightSon) > 0)
        {
            smallLeftRotation(dictionary, node);
            fixHeight(node->parent);
            return;
        }
        bigLeftRotation(dictionary, node);
        fixHeight(node->parent);
        return;
    }
    if (calculateHeightDifference(node->leftSon) < 0)
    {
        smallRightRotation(dictionary, node);
        fixHeight(node->parent);
        return;
    }
    bigRightRotation(dictionary, node);
    fixHeight(node->parent);
}

void rebalanceTree(Dictionary* dictionary, TreeNode* node)
{
    if (abs(calculateHeightDifference(node)) > 1)
    {
        rebalanceNode(dictionary, node);
        return;
    }
    if (node->parent != NULL)
    {
        node = node->parent;
        rebalanceTree(dictionary, node);
    }
}

void transfer(TreeNode* node, Direction directionOfSon)
{
    if (node->parent == NULL)
    {
        return;
    }
    if (directionOfSon == right)
    {
        node->rightSon->parent = node->parent;
    }
    else
    {
        node->leftSon->parent = node->parent;
    }
    if (node->parent->rightSon == node)
    {
        if (directionOfSon == right)
        {
            node->parent->rightSon = node->rightSon;
            node->rightSon = NULL;
            return;
        }
        node->parent->rightSon = node->leftSon;
        node->leftSon = NULL;
    }
    else
    {
        if (directionOfSon == right)
        {
            node->parent->leftSon = node->rightSon;
            node->rightSon = NULL;
            return;
        }
        node->parent->leftSon = node->leftSon;
        node->leftSon = NULL;
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
    free(branch->value);
    free(branch->key);
    free(branch);
}

void deleteDictionary(Dictionary** dictionary)
{
    if ((*dictionary) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*dictionary)->AVLTreeRoot);
    free(*dictionary);
    (*dictionary) = NULL;
}

void addEntry(Dictionary* dictionary, const char* key, char* value)
{
    if (dictionary->AVLTreeRoot == NULL)
    {
        TreeNode* newTreeNode = calloc(1, sizeof(TreeNode));
        newTreeNode->key = calloc(strlen(key) + 1, sizeof(char));
        newTreeNode->value = calloc(strlen(value) + 1, sizeof(char));
        strcat(newTreeNode->key, key);
        strcat(newTreeNode->value, value);
        dictionary->AVLTreeRoot = newTreeNode;
        return;
    }
    TreeNode* node = dictionary->AVLTreeRoot;
    while (true)
    {
        if (strcmp(key, node->key) == 0)
        {
            free(node->value);
            node->value = calloc(strlen(value) + 1, sizeof(char));
            strcat(node->value, value);
            return;
        }
        if (strcmp(key, node->key) > 0)
        {
            if (node->rightSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->key = calloc(strlen(key) + 1, sizeof(char));
                newNode->value = calloc(strlen(value) + 1, sizeof(char));
                strcat(newNode->key, key);
                strcat(newNode->value, value);
                newNode->parent = node;
                node->rightSon = newNode;
                node = newNode;
                fixHeight(newNode);
                rebalanceTree(dictionary, node);
                return;
            }
            node = node->rightSon;
        }
        else
        {
            if (node->leftSon == NULL)
            {
                TreeNode* newNode = calloc(1, sizeof(TreeNode));
                newNode->key = calloc(strlen(key) + 1, sizeof(char));
                newNode->value = calloc(strlen(value) + 1, sizeof(char));
                strcat(newNode->key, key);
                strcat(newNode->value, value);
                newNode->parent = node;
                node->leftSon = newNode;
                fixHeight(newNode);
                rebalanceTree(dictionary, node);
                return;
            }
            node = node->leftSon;
        }
    }
}

void freeNode(Dictionary* root, TreeNode* retrievableNode)
{
    if (root->AVLTreeRoot == retrievableNode)
    {
        free(retrievableNode->value);
        free((void*)retrievableNode->key);
        free(root->AVLTreeRoot);
        root->AVLTreeRoot = NULL;
        return;
    }
    if (retrievableNode->parent != NULL)
    {
        if (retrievableNode->parent->rightSon == retrievableNode)
        {
            retrievableNode->parent->rightSon = NULL;
            free(retrievableNode->value);
            free((void*)retrievableNode->key);
            free(retrievableNode);
            return;
        }
        retrievableNode->parent->leftSon = NULL;
        free(retrievableNode->value);
        free((void*)retrievableNode->key);
        free(retrievableNode);
    }
    else
    {
        free(retrievableNode->value);
        free((void*)retrievableNode->key);
        free(retrievableNode);
    }
}

void removeTreeNode(Dictionary* root, TreeNode* retrievableNode)
{
    if (root->AVLTreeRoot == NULL)
    {
        return;
    }
    bool isRoot = retrievableNode == root->AVLTreeRoot;
    if (retrievableNode->leftSon == NULL
            && retrievableNode->rightSon == NULL)
    {
        if (retrievableNode->parent != NULL)
        {
            TreeNode* balanceNode = retrievableNode->parent;
            freeNode(root, retrievableNode);
            fixHeight(balanceNode);
            rebalanceTree(root, balanceNode);
            return;
        }
        freeNode(root, retrievableNode);
        if (isRoot)
        {
            deleteDictionary(&root);
        }
        return;
    }
    if (retrievableNode->leftSon != NULL
            && retrievableNode->rightSon == NULL)
    {
        if (retrievableNode->parent != NULL)
        {
            TreeNode* balanceNode = retrievableNode->parent;
            transfer(retrievableNode, left);
            retrievableNode->parent = NULL;
            freeNode(root, retrievableNode);
            fixHeight(balanceNode);
            rebalanceTree(root, balanceNode);
            return;
        }
        transfer(retrievableNode, left);
        freeNode(root, retrievableNode);
        return;
    }
    if (retrievableNode->leftSon == NULL
            && retrievableNode->rightSon != NULL)
    {
        if (retrievableNode->parent != NULL)
        {
            TreeNode* balanceNode = retrievableNode->parent;
            transfer(retrievableNode, right);
            retrievableNode->parent = NULL;
            freeNode(root, retrievableNode);
            fixHeight(balanceNode);
            rebalanceTree(root, balanceNode);
            return;
        }
        transfer(retrievableNode, right);
        freeNode(root, retrievableNode);
        return;
    }
    TreeNode* newNode = retrievableNode->leftSon;
    while (newNode->rightSon != NULL)
    {
        newNode = newNode->rightSon;
    }
    retrievableNode->key = newNode->key;
    retrievableNode->value = newNode->value;
    newNode->parent->rightSon = newNode->leftSon;
    removeTreeNode(root, newNode);
}

TreeNode* findNode(Dictionary* root, const char* key)
{
    if (root == NULL || root->AVLTreeRoot == NULL)
    {
        return NULL;
    }
    TreeNode* node = root->AVLTreeRoot;
    while (true)
    {
        if (strcmp(key, node->key) == 0)
        {
            return node;
        }
        if (strcmp(key, node->key) > 0)
        {
            if (node->rightSon == NULL)
            {
                return NULL;
            }
            node = node->rightSon;
        }
        else
        {
            if (node->leftSon == NULL)
            {
                return NULL;
            }
            node = node->leftSon;
        }
    }
}

char* findValue(Dictionary* dictionary, const char* key)
{
    TreeNode* node = findNode(dictionary, key);
    if (node == NULL)
    {
        return NULL;
    }
    return node->value;
}

bool isKeyInDictionary(Dictionary* dictionary, const char* key)
{
    return findNode(dictionary, key) != NULL;
}

void removeEntry(Dictionary* dictionary, const char* key)
{
    TreeNode* node = findNode(dictionary, key);
    if (node != NULL)
    {
        removeTreeNode(dictionary, node);
    }
}

int getHeight(Dictionary* dictionary)
{
    if (dictionary->AVLTreeRoot == NULL)
    {
        return 0;
    }
    return (int) dictionary->AVLTreeRoot->height;
}