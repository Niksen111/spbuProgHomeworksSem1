#include <stdio.h>
#include "stack.h"

int main() {
    Stack* stack = createStack();
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    deleteStack(&stack);

}
