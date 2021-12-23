#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

char* getComment(FILE* file, int* currentIndex, StateTable* stateTable)
{
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
                comment[currentCommentLength] = c;
                ++currentCommentLength;
                break;
            }
            case 2:
            {
                comment[currentCommentLength] = c;
                ++currentCommentLength;
                break;
            }
            case 3:
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
    int currentIndex = 0;
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return;
    }
    while (true)
    {
        char* newComment = getComment(file, &currentIndex,  stateTable);
        if (newComment == NULL)
        {
            break;
        }
        printf("%s\n", newComment);
        free(newComment);
    }
    fclose(file);
}

int main()
{
    StateTable* stateTable = createStateTableFromFile("stateTable.txt");
    printAllComments("inputFile.txt", stateTable);\
    deleteStateTable(&stateTable);
    return 0;
}
