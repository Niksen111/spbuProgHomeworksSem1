#include "searchTreeTests.h"
#include "searchTree.h"
#include <string.h>
#include <stdlib.h>

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
    char* s1 = calloc(15, sizeof(char));
    strcat(s1, "Lul");
    char* s2 = calloc(15, sizeof(char));
    strcat(s2, "SearchTreeeee");
    char* s3 = calloc(15, sizeof(char));
    strcat(s3, "Elle");
    addEntry(root, 2, s2);
    addEntry(root, 1, s1);
    addEntry(root, 3, s3);
    deleteDictionary(&root);

    return root == NULL;
}

bool testAddEntry()
{
    Dictionary* root = createDictionary();
    char* s1 = calloc(15, sizeof(char));
    strcat(s1, "Lul");
    char* s2 = calloc(15, sizeof(char));
    strcat(s2, "SearchTreeeee");
    char* s3 = calloc(15, sizeof(char));
    strcat(s3, "Elle");
    char* s4 = calloc(15, sizeof(char));
    strcat(s4, "Mrs");
    addEntry(root, 2, s2);
    addEntry(root, 1, s1);
    bool result = findValue(root, 2) != NULL
            && findValue(root, 4) == NULL;
    addEntry(root, 4, s3);
    addEntry(root, 1, s4);
    result = result && findValue(root, 4) != NULL
            && strcmp(findValue(root, 1), s4) == 0;
    deleteDictionary(&root);

    return result;
}

bool testFindValue()
{
    Dictionary* root = createDictionary();
    char* s1 = calloc(15, sizeof(char));
    strcat(s1, "Lul");
    char* s2 = calloc(15, sizeof(char));
    strcat(s2, "SearchTreeeee");
    char* s3 = calloc(15, sizeof(char));
    strcat(s3, "Elle");
    addEntry(root, 2, s2);
    addEntry(root, 1, s1);
    addEntry(root, 3, s3);
    bool result = strcmp(findValue(root, 3), s3) == 0
            && findValue(root, 4) == NULL;
    deleteDictionary(&root);

    return result;
}

bool testisKeyInDictionary()
{
    Dictionary* root = createDictionary();
    char* s1 = calloc(15, sizeof(char));
    strcat(s1, "Lul");
    char* s2 = calloc(15, sizeof(char));
    strcat(s2, "SearchTreeeee");
    char* s3 = calloc(15, sizeof(char));
    strcat(s3, "Elle");
    addEntry(root, 2, s2);
    addEntry(root, 1, s1);
    addEntry(root, 3, s3);
    bool result = isKeyInDictionary(root, 2)
            && !isKeyInDictionary(root, 5)
            && isKeyInDictionary(root, 3);
    deleteDictionary(&root);

    return result;
}

bool testRemoveTheKey()
{
    Dictionary* root = createDictionary();
    char* s1 = calloc(15, sizeof(char));
    strcat(s1, "Kate");
    char* s2 = calloc(15, sizeof(char));
    strcat(s2, "Jess");
    char* s3 = calloc(15, sizeof(char));
    strcat(s3, "Elle");
    char* s4 = calloc(15, sizeof(char));
    strcat(s4, "Mary");
    char* s5 = calloc(15, sizeof(char));
    strcat(s5, "Eva");
    addEntry(root, 2, s2);
    addEntry(root, 1, s1);
    addEntry(root, 4, s3);
    addEntry(root, 3, s4);
    addEntry(root, 5, s5);
    bool result = isKeyInDictionary(root, 3);
    removeEntry(root, 3);
    result = result && !isKeyInDictionary(root, 3);
    deleteDictionary(&root);

    return result;
}

bool testSearchTree()
{
    return testCreateDictionary() && testDeleteDictionary()
        && testAddEntry() && testFindValue()
        && testisKeyInDictionary() && testRemoveTheKey();
}