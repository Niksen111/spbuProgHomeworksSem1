#include <stdio.h>
#include "stack.h"
#include "stackTests.h"

int main()
{
    if (!testStack())
    {
        printf("No\n");
        return -1;
    }
    Stack* stack = createStack();
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    deleteStack(&stack);
}
