#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int dividend = 0;
    int divisor = 0;
    printf("%s", "Enter dividend and divisor (integers): ");
    scanf_s("%d %d", &dividend, &divisor);

    while (divisor == 0)
    {
        printf("%s\n%s", "Divisor  is incorrect.",
            "Enter divisor again: ");
        scanf_s("%d", &divisor);
    }

    if (dividend == 0)
    {
        printf("%s %d\n", "The incomplete quotient is", 0);
        return 0;
    }

    int incompleteQuotient = 0;
    const int distinctionOfSigns = dividend / abs(dividend) * divisor / abs(divisor);

    while (dividend < 0 || dividend >= abs(divisor))
    {
        dividend = dividend - divisor * distinctionOfSigns;
        incompleteQuotient = incompleteQuotient + distinctionOfSigns;
    }

    printf("%s %i\n", "The incomplete quotient is", incompleteQuotient);
}
