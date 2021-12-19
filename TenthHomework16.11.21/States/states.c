#include "states.h"
#include <stdlib.h>
#include <stdio.h>
#include "sortedList.h"

typedef struct States
{
    int citiesNumber;
    int roadsNumber;
    int capitalsNumber;
    int** adjacencyMatrix;
    int* cities;
    int* capitals;
} States;

int** createAdjacencyMatrixFromFile(FILE* file, int citiesNumber, int roadsNumber)
{
    int** matrix = calloc(citiesNumber, sizeof(int*));
    for (int i = 0; i < citiesNumber; ++i)
    {
        matrix[i] = calloc(citiesNumber, sizeof(int));
    }
    for (int i = 0; i < roadsNumber; ++i)
    {
        int firstCity = 0;
        int secondCity = 0;
        int roadLength = 0;
        fscanf(file, "%d %d %d", &firstCity, &secondCity, &roadLength);
        matrix[firstCity][secondCity] = roadLength;
        matrix[secondCity][firstCity] = roadLength;
    }
    return matrix;
}

void freeMatrix(int*** matrix, int n)
{
    for (int i = 0; i < n; ++i)
    {
        free((*matrix)[i]);
    }
    free(*matrix);
}

void distributionCities(States* states)
{
    states->cities = calloc(states->citiesNumber, sizeof(int));
    SortedList** listsOfAddedCities = calloc(states->capitalsNumber, sizeof(SortedList*));
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        listsOfAddedCities[i] = createSortedList();
        push(&listsOfAddedCities[i], 0, states->capitals[i]);
    }
    bool allCitiesDistributed = false;
    while (!allCitiesDistributed)
    {
        allCitiesDistributed = true;
        for (int i = 0; i < states->capitalsNumber; ++i)
        {
            int errorCode = 0;
            while (!sortedListIsEmpty(listsOfAddedCities[i]) && states->cities[getNodeNumberFromHead(listsOfAddedCities[i])] != 0)
            {
                removeItemFromHead(&listsOfAddedCities[i], &errorCode);
            }
            if (sortedListIsEmpty(listsOfAddedCities[i]))
            {
                continue;
            }
            allCitiesDistributed = false;
            int indexOfAddedCity = getNodeNumberFromHead(listsOfAddedCities[i]);
            removeItemFromHead(&listsOfAddedCities[i], &errorCode);
            states->cities[indexOfAddedCity] = i + 1;
            for (int j = 0; j < states->citiesNumber; ++j)
            {
                if (states->adjacencyMatrix[indexOfAddedCity][j] != 0)
                {
                    push(&listsOfAddedCities[i], states->adjacencyMatrix[indexOfAddedCity][j], j);
                }
            }
        }
    }
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        deleteSortedList(&listsOfAddedCities[i]);
    }
    free(listsOfAddedCities);
}

States* createStatesFromFile(char fileName[])
{
    States* states = calloc(1, sizeof(States));
    FILE* file = fopen(fileName, "r");
    fscanf(file, "%d %d", &(states->citiesNumber), &(states->roadsNumber));
    states->adjacencyMatrix = createAdjacencyMatrixFromFile(file, states->citiesNumber, states->roadsNumber);
    fscanf(file, "%d", &(states->capitalsNumber));
    states->capitals = calloc(states->capitalsNumber, sizeof(int));
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        fscanf(file, "%d", &(states->capitals)[i]);
    }
    fclose(file);
    distributionCities(states);
    return states;
}

void deleteStates(States** states)
{
    free((*states)->cities);
    free((*states)->capitals);
    freeMatrix(&(*states)->adjacencyMatrix, (*states)->citiesNumber);
    free(*states);
    (*states) = NULL;
}

void printStates(States* states)
{
    SortedList** statesList = calloc(states->capitalsNumber, sizeof(SortedList*));
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        statesList[i] = createSortedList();
    }
    for (int i = states->citiesNumber - 1; i >= 0; --i)
    {
        push(&statesList[states->cities[i] - 1], i, i);
    }
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        printf("State Number %d.\n", i + 1);
        printf("The capital of the state is city Number %d.\n", states->capitals[i]);
        printf("Cities of this state:\n");
        int errorCode = 0;
        printf("%d", removeItemFromHead(&statesList[i], &errorCode));
        while (!sortedListIsEmpty(statesList[i]))
        {
            printf(", %d", removeItemFromHead(&statesList[i], &errorCode));
        }
        printf("\n\n");
    }
    for (int i = 0; i < states->capitalsNumber; ++i)
    {
        deleteSortedList(&statesList[i]);
    }
    free(statesList);
}

int getCitiesNumber(States* states)
{
    if (states == NULL)
    {
        return -1;
    }
    return states->citiesNumber;
}

int getRoadsNumber(States* states)
{
    if (states == NULL)
    {
        return -1;
    }
    return states->roadsNumber;
}

int getCapitalsNumber(States* states)
{
    if (states == NULL)
    {
        return -1;
    }
    return states->capitalsNumber;
}


int* getCapitalsList(States* states)
{
    if (states == NULL)
    {
        return NULL;
    }
    return states->capitals;
}


int* getCitiesList(States* states)
{
    if (states == NULL)
    {
        return NULL;
    }
    return states->cities;
}
