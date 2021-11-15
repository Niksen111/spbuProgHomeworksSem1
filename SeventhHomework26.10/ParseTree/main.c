#include <stdio.h>
#include <stdlib.h>
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

int main()
{
    if (!testParseTree())
    {
        printf("Tests failed(\n");
        return -1;
    }
    char* line = readLineFromFile("../file.txt\0");
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
