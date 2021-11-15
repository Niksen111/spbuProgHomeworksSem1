#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseTreeTests.h"
#include "parseTree.h"

char* readLineFromFile(char name[])
{
    FILE* file1 = fopen(name, "r");
    if (file1 == NULL)
    {
        printf("File not found(\n");
        return NULL;
    }
    int counter = 0;
    while (fscanf(file1, "%*c") >= 0)
    {
        ++counter;
    }
    rewind(file1);
    char* line = calloc(counter + 1, sizeof(char));
    fscanf(file1, "%[^\n]", line);
    fclose(file1);
    return line;
}

bool testReadLineFromFile()
{
    FILE* file1 = fopen("test1.txt", "w");
    fprintf(file1, "Lol kek mmm \n sldfds");
    fclose(file1);
    char* line = NULL;
    line = readLineFromFile("test1.txt");
    char lineAnswer[15] = "Lol kek mmm \0";

    return strcmp(line, lineAnswer) == 0;
}

int main()
{
    if (!testParseTree() || !testReadLineFromFile())
    {
        printf("Tests failed(\n");
        return -1;
    }
    char* line = readLineFromFile("file.txt\0");
    if (line == NULL)
    {
        return -2;
    }
    int errorCode = 0;
    ParseTree* myTree = createTree(line, &errorCode);
    printTree(myTree);
    printf("\n");
    int result = calculateValueOfTree(myTree);
    deleteTree(&myTree);
    printf("Result of the expression: %d\n", result);

    return 0;
}
