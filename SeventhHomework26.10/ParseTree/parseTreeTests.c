#include <stddef.h>
#include "parseTreeTests.h"
#include "parseTree.h"

bool testCreateTree()
{
    char expression1[20] = "(* (+ 1 1) 2)";
    int errorCode1 = 0;
    ParseTree* tree1 = createTree(expression1, &errorCode1);
    bool result = tree1 != NULL;
    deleteTree(&tree1);
    return result;
}

bool testDeleteTree()
{
    char expression1[20] = "(* (+ 1 1) 2)";
    int errorCode1 = 0;
    ParseTree* tree1 = createTree(expression1, &errorCode1);
    deleteTree(&tree1);
    return tree1 == NULL;
}

bool testCalculateValueOfTree()
{
    char expression1[20] = "(* (+ 1 1) 2)";
    int errorCode1 = 0;
    ParseTree* tree1 = createTree(expression1, &errorCode1);
    int result = calculateValueOfTree(tree1);
    deleteTree(&tree1);
    return result == 4;
}

bool testParseTree()
{
    return testCreateTree() && testCalculateValueOfTree()
        && testDeleteTree();
}