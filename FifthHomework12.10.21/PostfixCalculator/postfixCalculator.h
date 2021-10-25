#pragma once

// Returns the result of the expression in postfix form
int postfixCalculator(const char arraySymbols[], int* error);

// Outputs to the console the decoding of the postfix calculator error
void handleTheError(int errorCode);