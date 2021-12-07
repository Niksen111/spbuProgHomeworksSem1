#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findZero(const int theArray[], const int lengthOfArray, const int lastResult)
{
    for (int i = lastResult + 1; i < lengthOfArray; ++i)
    {
        if (theArray[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

void goAround(int** matrix, const int sizeOfMatrix, int start, int* passed)
{
    for (int i = 0; i < sizeOfMatrix; ++i)
    {
        if (matrix[start][i] == 1 && passed[i] == 0)
        {
            passed[i] = 1;
            printf(", %d", i + 1);
            goAround(matrix, sizeOfMatrix, i, passed);
        }
    }
}

void printTheConnectivityComponent(int** adjacencyMatrix, int nodesSize)
{
    int* passed = calloc(nodesSize, sizeof(int));
    int indexOfZero = findZero(passed, nodesSize, -1);
    int counter = 1;
    while (indexOfZero >= 0)
    {
        printf("Component %d, nodes: %d", counter, indexOfZero + 1);
        passed[0] = 1;
        goAround(adjacencyMatrix, nodesSize, indexOfZero, passed);
        indexOfZero = findZero(passed, nodesSize, indexOfZero);
        ++counter;
        printf("\n");
    }
}

int main()
{
    int nodesSize = 0;
    int edgesSize = 0;
    printf("Enter the number of nodes and edges:\n");
    scanf("%d %d", &nodesSize, &edgesSize);
    printf("Enter the incidence matrix:\n");
    int** incidenceMatrix = (int**) calloc(nodesSize, sizeof(int*));
    for (int i = 0; i < edgesSize; ++i)
    {
        incidenceMatrix[i] = calloc(edgesSize, sizeof(int));
    }
    for (int i = 0; i < nodesSize; ++i)
    {
        for (int j = 0; j < edgesSize; ++j)
        {
            scanf("%d", &incidenceMatrix[j][i]);
        }
    }

    int** adjacencyMatrix = (int**) calloc(nodesSize, sizeof(int*));
    for (int i = 0; i < nodesSize; ++i)
    {
        adjacencyMatrix[i] = calloc(nodesSize, sizeof(int));
    }
    for (int i = 0; i < edgesSize; ++i)
    {
        int firstEdge = -1;
        int secondEdge = -1;
        for (int j = 0; j < nodesSize; ++j)
        {
            if (incidenceMatrix[i][j] != 0)
            {
                if (firstEdge == -1)
                {
                    firstEdge = j;
                }
                else
                {
                    secondEdge = j;
                }
            }
        }
        adjacencyMatrix[firstEdge][secondEdge] = 1;
        adjacencyMatrix[secondEdge][firstEdge] = 1;
    }
    printTheConnectivityComponent(adjacencyMatrix, nodesSize);
    return 0;
}