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
    char expression2[40] = "(+ 1 (* 2 (- 3 (/ 4 2))))";
    int errorCode1 = 0;
    int errorCode2 = 0;
    ParseTree* tree1 = createTree(expression1, &errorCode1);
    ParseTree* tree2 = createTree(expression2, &errorCode2);
    bool result = calculateValueOfTree(tree1) == 4 && errorCode1 == 0
            && calculateValueOfTree(tree2) == 3 && errorCode2 == 0;
    deleteTree(&tree1);
    deleteTree(&tree2);
    return result;
}

bool testParseTree()
{
    return testCreateTree() && testCalculateValueOfTree()
        && testDeleteTree();
}