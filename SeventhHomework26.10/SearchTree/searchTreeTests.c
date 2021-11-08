#include "searchTreeTests.h"
#include "searchTree.h"
#include <stdlib.h>

bool testCreateTreeRoot()
{
    TreeRoot* root = createTreeRoot();
    bool result = root == NULL;
    deleteTree(&root);

    return result;
}

bool testDeleteTree()
{
    return true;
}

bool testAddTreeNode()
{
    return true;
}

bool testFindValue()
{
    return true;
}

bool testIsKeyInTree()
{
    return true;
}

bool testRemoveTheKey()
{
    return true;
}

bool testSearchTree()
{
    return testCreateTreeRoot() && testDeleteTree()
        && testAddTreeNode() && testFindValue()
        && testIsKeyInTree() && testRemoveTheKey();
}