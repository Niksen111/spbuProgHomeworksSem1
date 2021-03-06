#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct StateTable
{
    int columnNumber;
    int rowNumber;
    int** table;
} StateTable;

void deleteStateTable(StateTable** stateTable)
{
    for (int i = 0; i < (*stateTable)->rowNumber; ++i)
    {
        free((*stateTable)->table[i]);
    }
    free((*stateTable)->table);
    free(*stateTable);
    (*stateTable) = NULL;
}

int getNumber(char c)
{
    switch (c)
    {
        case '/':
            return 0;
        case '*':
            return 1;
        default:
            return 2;
    }
}

StateTable* createStateTableFromFile(const char fileName[])
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    StateTable* stateTable = calloc(1, sizeof(StateTable));
    if (stateTable == NULL)
    {
        fclose(file);
        return NULL;
    }
    fscanf(file, "%d %d%*c", &stateTable->columnNumber, &stateTable->rowNumber);
    stateTable->table = calloc(stateTable->rowNumber, sizeof(int*));
    fscanf(file, "%*[^\n]");
    for (int i = 0; i < stateTable->rowNumber; ++i)
    {
        stateTable->table[i] = calloc(stateTable->columnNumber, sizeof(int));
        for (int j = 0; j < stateTable->columnNumber; ++j)
        {
            fscanf(file, "%d", &stateTable->table[i][j]);
        }
    }
    fclose(file);
    return stateTable;
}

char* getComment(FILE* file, StateTable* stateTable)
{
    if (stateTable == NULL)
    {
        return NULL;
    }
    char* comment = calloc(1000, sizeof(char));
    if (comment == NULL)
    {
        return NULL;
    }
    int state = 0;
    int currentCommentLength = 0;
    char c = '\0';
    while (fscanf(file, "%c", &c) >= 0)
    {
        int column = getNumber(c);
        state = stateTable->table[state][column];
        switch (state)
        {
            case 0:
            {
                comment[0] = '\0';
                currentCommentLength = 0;
                break;
            }
            case 1:
            {
                comment[0] = '/';
                currentCommentLength = 1;
                break;
            }
            case 3:
            case 2:
            {
                comment[currentCommentLength] = c;
                ++currentCommentLength;
                break;
            }
            default:
            {
                comment[currentCommentLength] = c;
                return comment;
            }
        }
    }
    free(comment);
    return NULL;
}

void printAllComments(const char fileName[], StateTable* stateTable)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return;
    }
    while (true)
    {
        char* newComment = getComment(file,  stateTable);
        if (newComment == NULL)
        {
            break;
        }
        printf("%s\n", newComment);
        free(newComment);
    }
    fclose(file);
}

bool testCreateStateTableFromFile()
{
    StateTable* stateTable = createStateTableFromFile("stateTable.txt");
    bool result = stateTable->rowNumber == 4 && stateTable->columnNumber == 3;
    int tableResult[12] = { 1, 0, 0, 1, 2, 0, 2, 3, 2, 4, 3, 2 };
    for (int i = 0; i < stateTable->rowNumber; ++i)
    {
        for (int j = 0; j < stateTable->columnNumber; ++j)
        {
            result = result && tableResult[i * stateTable->columnNumber + j] == stateTable->table[i][j];
        }
    }
    deleteStateTable(&stateTable);
    return result;
}

bool testDeleteStateTable()
{
    StateTable* stateTable = createStateTableFromFile("stateTable.txt");
    bool result = stateTable->rowNumber == 4 && stateTable->columnNumber == 3
        && stateTable->table[0][0] == 1;
    deleteStateTable(&stateTable);
    result = result && stateTable == NULL;

    return result;
}

bool testGetComment()
{
    StateTable* stateTable = createStateTableFromFile("stateTable.txt");
    FILE* file = fopen("inputFile.txt", "r");
    if (file == NULL)
    {
        deleteStateTable(&stateTable);
        return true;
    }
    char* newComment = getComment(file,  stateTable);
    if (newComment == NULL)
    {
        deleteStateTable(&stateTable);
        return false;
    }
    bool result = strcmp(newComment, "/* adds an item to the list*/") == 0;
    free(newComment);
    newComment = getComment(file,  stateTable);
    if (newComment == NULL)
    {
        deleteStateTable(&stateTable);
        return false;
    }
    result = result && strcmp(newComment, "/* returns a pointer to the first position of the list*/") == 0;
    free(newComment);
    deleteStateTable(&stateTable);

    return result;
}

int main()
{
    if (!testCreateStateTableFromFile() || !testDeleteStateTable()
        || !testGetComment())
    {
        printf("Tests failed :)\n");
        return -1;
    }
    StateTable* stateTable = createStateTableFromFile("stateTable.txt");
    printAllComments("inputFile.txt", stateTable);
    deleteStateTable(&stateTable);
    return 0;
}
