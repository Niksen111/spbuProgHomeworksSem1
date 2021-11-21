#include "avlTree.h"
#include <stdlib.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode
{
    int key;
    char* value;
    int heightDifference;
    int height;
    TreeNode* parent;
    TreeNode* leftSon;
    TreeNode* rightSon;
} TreeNode;

typedef struct AVLTreeRoot
{
    TreeNode* AVLTreeRoot;
} AVLTreeRoot;

typedef struct CurrentTreeNode
{
    TreeNode* currentTreeNode;
} CurrentTreeNode;

AVLTreeRoot* createAVLTreeRoot()
{
    return calloc(1, sizeof(AVLTreeRoot));
}

typedef enum Direction
{
    left,
    right
} Direction;

int calculateNodeHigh(TreeNode* node)
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

void recalculateHeightsRecursive(TreeNode* node)
{
    if (node == NULL)
    {
        return;
    }
    recalculateHeightsRecursive(node->leftSon);
    recalculateHeightsRecursive(node->rightSon);
    node->height = calculateNodeHigh(node);
    if (node->rightSon != NULL && node->leftSon != NULL)
    {
        node->heightDifference = node->rightSon->height - node->leftSon->height;
        return;
    }
    if (node->rightSon != NULL)
    {
        node->heightDifference = node->rightSon->height + 1;
        return;
    }
    if (node->leftSon != NULL)
    {
        node->heightDifference = -node->leftSon->height + 1;
    }
}

void recalculateHeights(AVLTreeRoot* root)
{
    if (root == NULL)
    {
        return;
    }
    recalculateHeightsRecursive(root->AVLTreeRoot);
}

void smallLeftRotation(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (root->AVLTreeRoot == node->currentTreeNode)
    {
        root->AVLTreeRoot = node->currentTreeNode->rightSon;
    }
    if (node->currentTreeNode->parent != NULL)
    {
        if (node->currentTreeNode->parent->rightSon == node->currentTreeNode)
        {
            node->currentTreeNode->parent->rightSon = node->currentTreeNode->rightSon;
        }
        else
        {
            node->currentTreeNode->parent->leftSon = node->currentTreeNode->rightSon;
        }
        node->currentTreeNode->rightSon->parent = node->currentTreeNode->parent;
    }
    else
    {
        node->currentTreeNode->rightSon->parent = NULL;
    }
    node->currentTreeNode->rightSon->leftSon->parent = node->currentTreeNode;
    node->currentTreeNode->parent = node->currentTreeNode->rightSon;
    node->currentTreeNode->rightSon = node->currentTreeNode->rightSon->leftSon;
    node->currentTreeNode->parent->leftSon = node->currentTreeNode;
}

void smallRightRotation(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (root->AVLTreeRoot == node->currentTreeNode)
    {
        root->AVLTreeRoot = node->currentTreeNode->leftSon;
    }
    if (node->currentTreeNode->parent != NULL)
    {
        if (node->currentTreeNode->parent->rightSon == node->currentTreeNode)
        {
            node->currentTreeNode->parent->rightSon = node->currentTreeNode->leftSon;
        }
        else
        {
            node->currentTreeNode->parent->leftSon = node->currentTreeNode->leftSon;
        }
        node->currentTreeNode->leftSon->parent = node->currentTreeNode->parent;
    }
    else
    {
        node->currentTreeNode->leftSon->parent = NULL;
    }
    node->currentTreeNode->leftSon->rightSon->parent = node->currentTreeNode;
    node->currentTreeNode->parent = node->currentTreeNode->leftSon;
    node->currentTreeNode->leftSon = node->currentTreeNode->leftSon->rightSon;
    node->currentTreeNode->parent->rightSon = node->currentTreeNode;
}

void bigLeftRotation(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (root->AVLTreeRoot == node->currentTreeNode)
    {
        root->AVLTreeRoot = node->currentTreeNode->rightSon->leftSon;
    }
    if (node->currentTreeNode->parent != NULL)
    {
        if (node->currentTreeNode->parent->rightSon == node->currentTreeNode)
        {
            node->currentTreeNode->parent->rightSon = node->currentTreeNode->rightSon->leftSon;
        }
        else
        {
            node->currentTreeNode->parent->leftSon = node->currentTreeNode->rightSon->leftSon;
        }
        node->currentTreeNode->rightSon->leftSon->parent = node->currentTreeNode->parent;
    }
    else
    {
        node->currentTreeNode->rightSon->leftSon->parent = NULL;
    }
    node->currentTreeNode->rightSon->leftSon->leftSon->parent = node->currentTreeNode;
    node->currentTreeNode->rightSon->leftSon->rightSon->parent = node->currentTreeNode->rightSon;
    node->currentTreeNode->parent = node->currentTreeNode->rightSon->leftSon;
    node->currentTreeNode->rightSon->leftSon = node->currentTreeNode->rightSon->leftSon->rightSon;
    node->currentTreeNode->rightSon->parent = node->currentTreeNode->rightSon->leftSon;
    node->currentTreeNode->parent->rightSon = node->currentTreeNode->rightSon;
    node->currentTreeNode->rightSon = node->currentTreeNode->parent->leftSon;
    node->currentTreeNode->parent->leftSon = node->currentTreeNode;
}

void bigRightRotation(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (root->AVLTreeRoot == node->currentTreeNode)
    {
        root->AVLTreeRoot = node->currentTreeNode->leftSon->rightSon;
    }
    if (node->currentTreeNode->parent != NULL)
    {
        if (node->currentTreeNode->parent->rightSon == node->currentTreeNode)
        {
            node->currentTreeNode->parent->rightSon = node->currentTreeNode->leftSon->rightSon;
        }
        else
        {
            node->currentTreeNode->parent->leftSon = node->currentTreeNode->leftSon->rightSon;
        }
        node->currentTreeNode->leftSon->rightSon->parent = node->currentTreeNode->parent;
    }
    else
    {
        node->currentTreeNode->leftSon->rightSon->parent = NULL;
    }
    node->currentTreeNode->leftSon->rightSon->rightSon->parent = node->currentTreeNode;
    node->currentTreeNode->leftSon->rightSon->leftSon->parent = node->currentTreeNode->leftSon;
    node->currentTreeNode->parent = node->currentTreeNode->leftSon->rightSon;
    node->currentTreeNode->leftSon->rightSon = node->currentTreeNode->leftSon->rightSon->leftSon;
    node->currentTreeNode->leftSon->parent = node->currentTreeNode->leftSon->rightSon;
    node->currentTreeNode->parent->leftSon = node->currentTreeNode->leftSon;
    node->currentTreeNode->leftSon = node->currentTreeNode->parent->rightSon;
    node->currentTreeNode->parent->rightSon = node->currentTreeNode;
}

void rebalanceNode(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (node->currentTreeNode->heightDifference < 0)
    {
        if (node->currentTreeNode->leftSon->heightDifference < 0)
        {
            smallRightRotation(root, node);
            return;
        }
        bigRightRotation(root, node);
        return;
    }
    if (node->currentTreeNode->leftSon->heightDifference)
    {
        smallLeftRotation(root, node);
        return;
    }
    bigLeftRotation(root, node);
}

void rebalanceTree(AVLTreeRoot* root, CurrentTreeNode* node)
{
    if (abs(node->currentTreeNode->heightDifference) > 1)
    {
        rebalanceNode(root, node);
        recalculateHeights(root);
        return;
    }
    if (node->currentTreeNode->parent != NULL)
    {
        node->currentTreeNode = node->currentTreeNode->parent;
        rebalanceTree(root, node);
    }
}

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

void deleteTree(AVLTreeRoot** root)
{
    if ((*root) == NULL)
    {
        return;
    }
    deleteBranchRecursive((*root)->AVLTreeRoot);
    (*root) = NULL;
}

void addTreeNode(AVLTreeRoot** root, int key, char* value)
{
    if ((*root)->AVLTreeRoot == NULL)
    {
        TreeNode* newTreeNode = calloc(1, sizeof(TreeNode));
        newTreeNode->key = key;
        newTreeNode->value = value;
        (*root)->AVLTreeRoot = newTreeNode;
        return;
    }
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    node->currentTreeNode = (*root)->AVLTreeRoot;
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
                node->currentTreeNode = newNode;
                recalculateHeights(*root);
                rebalanceTree(*root, node);
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
                recalculateHeights(*root);
                rebalanceTree(*root, node);
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

void freeNode(AVLTreeRoot** root, CurrentTreeNode** retrievableNode)
{
    if ((*root)->AVLTreeRoot == (*retrievableNode)->currentTreeNode)
    {
        free((*root)->AVLTreeRoot);
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

void removeTreeNode(AVLTreeRoot** root, CurrentTreeNode** retrievableNode)
{
    if ((*root)->AVLTreeRoot == NULL)
    {
        return;
    }
    bool isRoot = (*retrievableNode)->currentTreeNode == (*root)->AVLTreeRoot;
    if ((*retrievableNode)->currentTreeNode->leftSon == NULL
            && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        if ((*retrievableNode)->currentTreeNode->parent != NULL)
        {
            CurrentTreeNode* balanceNode = calloc(1, sizeof(CurrentTreeNode));
            balanceNode->currentTreeNode = (*retrievableNode)->currentTreeNode->parent;
            freeNode(root, retrievableNode);
            recalculateHeights(*root);
            rebalanceTree(*root, balanceNode);
            free(balanceNode);
            return;
        }
        freeNode(root, retrievableNode);
        if (isRoot)
        {
            deleteTree(root);
        }
        return;
    }
    if ((*retrievableNode)->currentTreeNode->leftSon != NULL
            && (*retrievableNode)->currentTreeNode->rightSon == NULL)
    {
        if ((*retrievableNode)->currentTreeNode->parent != NULL)
        {
            CurrentTreeNode* balanceNode = calloc(1, sizeof(CurrentTreeNode));
            balanceNode->currentTreeNode = (*retrievableNode)->currentTreeNode->parent;
            transfer((*retrievableNode), right);
            freeNode(root, retrievableNode);
            recalculateHeights(*root);
            rebalanceTree(*root, balanceNode);
            free(balanceNode);
            return;
        }
        transfer((*retrievableNode), right);
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
        if ((*retrievableNode)->currentTreeNode->parent != NULL)
        {
            CurrentTreeNode* balanceNode = calloc(1, sizeof(CurrentTreeNode));
            balanceNode->currentTreeNode = (*retrievableNode)->currentTreeNode->parent;
            transfer((*retrievableNode), left);
            freeNode(root, retrievableNode);
            recalculateHeights(*root);
            rebalanceTree(*root, balanceNode);
            free(balanceNode);
            return;
        }
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

CurrentTreeNode* findNode(AVLTreeRoot* root, int key)
{
    if (root == NULL || root->AVLTreeRoot == NULL)
    {
        return NULL;
    }
    CurrentTreeNode* node = calloc(1, sizeof(CurrentTreeNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->currentTreeNode = root->AVLTreeRoot;
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

char* findValue(AVLTreeRoot* root, int key)
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

bool isKeyInTree(AVLTreeRoot* root, int key)
{
    CurrentTreeNode* node = findNode(root, key);
    if (node != NULL)
    {
        free(node);
        return true;
    }
    return false;
}

void removeEntry(AVLTreeRoot** root, int key)
{
    CurrentTreeNode* node = findNode((*root), key);
    if (node != NULL)
    {
        removeTreeNode(root, &node);
    }
} 