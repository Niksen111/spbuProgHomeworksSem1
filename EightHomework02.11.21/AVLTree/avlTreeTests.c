#include "avlTreeTests.h"
#include "avlTree.h"
#include <string.h>

bool testCreateDictionary()
{
    Dictionary* root = createDictionary();
    bool result = root != NULL;
    deleteDictionary(&root);

    return result;
}

bool testDeleteDictionary()
{
    Dictionary* root = createDictionary();
    addEntry(root, "Jess", "Jess");
    addEntry(root, "Kate", "Kate");
    addEntry(root, "Elle", "Elle");
    deleteDictionary(&root);

    return root == NULL;
}

bool testAddEntry()
{
    Dictionary* root = createDictionary();
    addEntry(root, "Jess", "Jess");
    bool result = findValue(root, "Jess") != NULL
            && findValue(root, "Mary") == NULL;
    addEntry(root, "Eva", "Eva");
    addEntry(root, "Elle", "Elle");
    addEntry(root, "Mary", "Mary");
    result = result && findValue(root, "Mary") != NULL
            && strcmp(findValue(root, "Mary"), "Mary") == 0;
    deleteDictionary(&root);

    return result;
}

bool testFindValue()
{
    Dictionary* root = createDictionary();
    addEntry(root, "Jess", "Jess");
    addEntry(root, "Kate", "Kate");
    addEntry(root, "Elle", "Elle");
    bool result = strcmp(findValue(root, "Elle"), "Elle") == 0
            && findValue(root, "fdf") == NULL;
    deleteDictionary(&root);

    return result;
}

bool testisKeyInDictionary()
{
    Dictionary* root = createDictionary();
    addEntry(root, "Jess", "Jess");
    addEntry(root, "Kate", "Kate");
    addEntry(root, "Elle", "Elle");
    bool result = isKeyInDictionary(root, "Jess")
            && !isKeyInDictionary(root, "5")
            && isKeyInDictionary(root, "Elle");
    deleteDictionary(&root);

    return result;
}

bool testRemoveTheKey()
{
    Dictionary* root = createDictionary();
    bool result = getHeight(root) == 0;
    addEntry(root, "Kate", "Kate");
    result = result && getHeight(root) == 0;
    addEntry(root, "Jess", "Jess");
    result = result && getHeight(root) == 1;
    addEntry(root, "Elle", "Elle");
    result = result && getHeight(root) == 1;
    addEntry(root, "Mary", "Mary");
    result = result && getHeight(root) == 2;
    addEntry(root, "Eva", "Eva");
    result = result && isKeyInDictionary(root, "Elle") && getHeight(root) == 2;
    removeEntry(root, "Elle");
    result = result && !isKeyInDictionary(root, "Elle");
    deleteDictionary(&root);

    return result;
}

bool testGetHeight()
{
    Dictionary* root = createDictionary();
    addEntry(root, "Kate", "Kate");
    addEntry(root, "Jess", "Jess");
    addEntry(root, "Elle", "Elle");
    addEntry(root, "Mary", "Mary");
    addEntry(root, "Eva", "Eva");
    bool result = isKeyInDictionary(root, "Elle") && getHeight(root) == 2;
    removeEntry(root, "Elle");
    result = result && !isKeyInDictionary(root, "Elle");
    deleteDictionary(&root);

    return result;
}

bool testDictionary()
{
    return testCreateDictionary() && testDeleteDictionary()
            && testAddEntry() && testFindValue()
            && testisKeyInDictionary() && testRemoveTheKey()
            && testGetHeight();
} 