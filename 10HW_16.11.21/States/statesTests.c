#include "statesTests.h"
#include "sortedListTests.h"
#include "states.h"
#include <stdlib.h>

bool areArraysIdentical(const int array1[], const int array2[], int lengthOfArrays)
{
    for (int i = 0; i < lengthOfArrays; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool testCreateStatesFromFile()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCitiesNumber(states) == 5
            && getCapitalsNumber(states) == 2
            && getRoadsNumber(states) == 4;
    int* cities = getCitiesList(states);
    int citiesResult[5] = { 1, 1, 1, 2, 2 };
    result = result && areArraysIdentical(cities, citiesResult, 5);
    int* capitals = getCapitalsList(states);
    int capitalsResult[2] = { 0, 4};
    result = result && areArraysIdentical(capitals, capitalsResult, 2);
    deleteStates(&states);

    return result;
}

bool testDeleteStates()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCitiesNumber(states) == 5
            && getCapitalsNumber(states) == 2
            && getRoadsNumber(states) == 4;
    deleteStates(&states);
    result = result && states == NULL;

    return result;
}

bool testGetCitiesNumber()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCitiesNumber(states) == 5;
    deleteStates(&states);

    return result;
}

bool testGetRoadsNumber()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getRoadsNumber(states) == 4;
    deleteStates(&states);

    return result;
}

bool testGetCapitalsNumber()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCapitalsNumber(states) == 2;
    deleteStates(&states);

    return result;
}

bool testGetCapitalsList()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCitiesNumber(states) == 5
            && getCapitalsNumber(states) == 2
            && getRoadsNumber(states) == 4;
    int* capitals = getCapitalsList(states);
    int capitalsResult[2] = { 0, 4};
    result = result && areArraysIdentical(capitals, capitalsResult, 2);
    deleteStates(&states);

    return result;
}

bool testGetCitiesList()
{
    States* states = createStatesFromFile("file.txt");
    bool result = getCitiesNumber(states) == 5
            && getCapitalsNumber(states) == 2
            && getRoadsNumber(states) == 4;
    int* cities = getCitiesList(states);
    int citiesResult[5] = { 1, 1, 1, 2, 2 };
    result = result && areArraysIdentical(cities, citiesResult, 5);
    deleteStates(&states);

    return result;
}

bool testStates()
{
    return testCreateStatesFromFile() && testDeleteStates()
        && testGetCitiesNumber() && testGetRoadsNumber()
        && testGetCapitalsNumber() && testGetCapitalsList()
        && testGetCitiesList() && testSortedList();
}