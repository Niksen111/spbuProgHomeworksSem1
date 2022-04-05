#pragma once
#include <stdbool.h>

// returns the minimum of the two values
unsigned long min(unsigned long first, unsigned long second);

// checks if the first line is the smallest in the lexicographical order
bool isFirstEarlier(const char* first, const char* second);