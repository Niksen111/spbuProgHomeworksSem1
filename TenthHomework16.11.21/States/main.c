#include "sortedListTests.h"
#include "sortedList.h"
#include <stdio.h>
#include <stdlib.h>

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

int* distributionCities(int** matrix, int* capitals, int citiesNumber, int capitalsNumber)
{
    int* cities = calloc(citiesNumber, sizeof(int));
    SortedList** listsOfAddedCities = calloc(capitalsNumber, sizeof(SortedList*));
    for (int i = 0; i < capitalsNumber; ++i)
    {
        listsOfAddedCities[i] = createSortedList();
        push(&listsOfAddedCities[i], 0, capitals[i]);
    }
    bool allCitiesDistributed = false;
    while (!allCitiesDistributed)
    {
        allCitiesDistributed = true;
        for (int i = 0; i < capitalsNumber; ++i)
        {
            int errorCode = 0;
            while (!sortedListIsEmpty(listsOfAddedCities[i]) && cities[getNodeNumberFromHead(listsOfAddedCities[i])] != 0)
            {
                removeItemFromHead(&listsOfAddedCities[i], &errorCode);
            }
            if (sortedListIsEmpty(listsOfAddedCities[i]))
            {
                continue;
            }
            allCitiesDistributed = false;
            int indexOfAddedCity = getNodeNumberFromHead(listsOfAddedCities[i]);
            removeItemFromHead(&listsOfAddedCities[i], &indexOfAddedCity);
            cities[indexOfAddedCity] = i + 1;
            for (int j = 0; j < citiesNumber; ++j)
            {
                if (matrix[indexOfAddedCity][j] != 0)
                {
                    push(&listsOfAddedCities[i], matrix[indexOfAddedCity][j], j);
                }
            }
        }
    }
    for (int i = 0; i < capitalsNumber; ++i)
    {
        deleteSortedList(&listsOfAddedCities[i]);
    }
    free(listsOfAddedCities);

    return cities;
}

void printStatesAndCities(char* nameOfFile)
{
    int citiesNumber = 0;
    int roadsNumber = 0;
    FILE* file = fopen(nameOfFile, "r");
    fscanf(file, "%d %d", &citiesNumber, &roadsNumber);
    int** matrix = createAdjacencyMatrixFromFile(file, citiesNumber, roadsNumber);
    int capitalsNumber = 0;
    fscanf(file, "%d", &capitalsNumber);
    int* capitals = calloc(capitalsNumber, sizeof(int));
    for (int i = 0; i < capitalsNumber; ++i)
    {
        fscanf(file, "%d", &capitals[i]);
    }
    fclose(file);
    int* cities = distributionCities(matrix, capitals, citiesNumber, capitalsNumber);
    freeMatrix(&matrix);
    int** states = calloc(capitalsNumber, sizeof(int*));
    for (int i = 0; i < capitalsNumber; ++i)
    {
        states[i] = calloc(citiesNumber, sizeof(int));
    }
    for (int i = 0; i < citiesNumber; ++i)
    {
        
    }
}

int main()
{
    if (!testSortedList())
    {
        printf("Tests failed :(\n");
        return -1;
    }
    return 0;
}
