#include <stdio.h>
#include <string.h>

int main()
{
    //This array will keep the numbers of all possible sums of the three numbers

    int theArray[28] = { 0 };

    //Fun fact:
    // the second half of the Array is just reversed the first half of the Array
    //but we will not use this.

    //We create all possible sums of the three numbers
    //(0 + 0 + 0; 0 + 0 + 1; ...; 9 + 9 + 8; 9 + 9 + 9)
    //And are counting the number of each possible sum

    for (int i = 0; i <= 9; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= 9; ++k)
            {
                ++theArray[i + j + k];
            }
        }
    }

    //The number of all lucky tickets is counted as
    //the sum of all squares of the Array elements

    int numberOfAllLuckyTickets = 0;

    for (int i = 0; i < 28; ++i)
    {
        numberOfAllLuckyTickets += theArray[i] * theArray[i];
    }

    printf("%s %d", "The number of all lucky tickets is", numberOfAllLuckyTickets);
}
