#include "supportFunctions.h"
#include <string.h>

unsigned long min(unsigned long first, unsigned long second)
{
    return first < second ? first : second;
}

bool isFirstEarlier(const char* first, const char* second)
{
    const unsigned long lengthOfShorterString = min(strlen(first), strlen(second));
    for (int i = 0; i < lengthOfShorterString; ++i)
    {
        if (first[i] < second[i])
        {
            return true;
        }
        if (first[i] > second[i])
        {
            return false;
        }
    }
    return strlen(first) <= strlen(second);
}