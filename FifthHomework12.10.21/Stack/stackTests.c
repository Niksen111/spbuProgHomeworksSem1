#include "stackTests.h"
#include "stack.h"
#include <stdio.h>

bool testCreateStack()
{
    Stack* head = createStack();
    bool result = head == NULL;
    deleteStack(&head);

    return result;
}

bool testPush()
{
    Stack* head = createStack();
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    bool result = head->value == 30 &&
                  head->next->value == 20 &&
                  head->next->next->value == 10;
    deleteStack(&head);

    return result;
}

bool testPop()
{
    Stack* head = createStack();
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    int errorCode = 0;

    return pop(&head, &errorCode) == 30 &&
        pop(&head, &errorCode) == 20 &&
        pop(&head, &errorCode) == 10 &&
        pop(&head, &errorCode) == 0 && errorCode == -1;
}

bool testStackIsEmpty()
{
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();
    push(&stack2, 10);
    bool result = stackIsEmpty(&stack1) == true &&
                stackIsEmpty(&stack2) == false;
    deleteStack(&stack1);
    deleteStack(&stack2);

    return result;
}

bool testDeleteStack()
{
    Stack* stack1 = createStack();
    Stack* head = createStack();
    push(&head, 10);
    push(&head, 20);
    deleteStack(&stack1);
    deleteStack(&head);

    return head == NULL && stack1 == NULL;
}

bool testStack()
{
    return testCreateStack() && testDeleteStack() &&
        testPop() && testPush() && testStackIsEmpty();
}