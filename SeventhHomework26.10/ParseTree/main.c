#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseTreeTests.h"
#include "parseTree.h"

char* readLineFromFile(const char name[])
{
    FILE* file = fopen(name, "r");
    if (file == NULL)
    {
        printf("File not found(\n");
        return NULL;
    }
    int counter = 0;
    while (fscanf(file, "%*c") >= 0)
    {
        ++counter;
    }
    rewind(file);
    char* line = calloc(counter + 1, sizeof(char));
    fscanf(file, "%[^\n]", line);
    fclose(file);
    return line;
}

bool testReadLineFromFile()
{
    FILE* file1 = fopen("test1.txt", "w");
    fprintf(file1, "Lol kek mmm \n sldfds");
    fclose(file1);
    const char* line = readLineFromFile("test1.txt");
    const char lineAnswer[15] = "Lol kek mmm ";
    bool result = strcmp(line, lineAnswer) == 0;
    free((void*)line);

    return result;
}

int main()
{
    if (!testParseTree() || !testReadLineFromFile())
    {
        printf("Tests failed(\n");
        return -1;
    }
    char* line = readLineFromFile("file.txt");
    if (line == NULL)
    {
        return -2;
    }
    int errorCode = 0;
    ParseTree* myTree = createTree(line, &errorCode);
    free(line);
    printTree(myTree);
    printf("\n");
    int result = calculateValueOfTree(myTree);
    deleteTree(&myTree);
    printf("Result of the expression: %d\n", result);

    return 0;
}
