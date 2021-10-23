#pragma once
#include "stdbool.h"

// checks if the brackets are balanced
bool areBracketsBalanced(const char bracketsList[], int *errorCode);

// Outputs to the console the decoding of the bracketBalance error
void handleTheError(int errorCode);