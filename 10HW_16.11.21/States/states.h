#pragma once

// States structure
typedef struct States States;

// creates states based on the file
States* createStatesFromFile(const char fileName[]);

// deletes all the states
void deleteStates(States** states);

// prints all the States with their cities and capital
void printStates(States* states);

// returns number of cities in the States
int getCitiesNumber(States* states);

// returns number of roads in the States
int getRoadsNumber(States* states);

// returns number of capitals in the States
int getCapitalsNumber(States* states);

// returns list of all the capitals
int* getCapitalsList(States* states);

// returns list of all the cities
int* getCitiesList(States* states);