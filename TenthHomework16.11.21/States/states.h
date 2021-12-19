#pragma once

typedef struct States States;

States* createStatesFromFile(char fileName[]);

void deleteStates(States** states);

void printStates(States* states);

int getCitiesNumber(States* states);

int getRoadsNumber(States* states);

int getCapitalsNumber(States* states);

int* getCapitalsList(States* states);

int* getCitiesList(States* states);