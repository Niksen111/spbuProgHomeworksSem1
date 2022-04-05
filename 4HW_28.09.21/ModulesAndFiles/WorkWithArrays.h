#pragma once
#include <stdbool.h>

// Exchanges the values of two variables
void swap(int* firstVariable, int* secondVariable);

// Prints an array of a given length to the console
void printArray(const int theArray[], const int lengthOfTheArray);

// Fills the array with random elements
void fillArrayWithRandomElements(int theArray[], int lengthOfTheArray, int mod);

// Checks if the array is sorted
bool checkThatArrayIsSorted(const int theArray[], const int lengthOfTheArray);

// Check if the arrays are identical
bool checkThatAnArraysAreIdentical(const int firstArray[],
                                   const int secondArray[], const int lengthOfArrays);