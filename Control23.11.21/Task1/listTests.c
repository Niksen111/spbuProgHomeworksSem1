#include "listTests.h"
#include "list.h"
#include <stdlib.h>

bool testCreateList()
{
    List * head = createList();
    bool result = head == NULL;
    deleteList(head);

    return result;
}

bool testListIsEmpty()
{
    List* list1 = createList();
    List* list2 = createList();
    Position* position = createPosition();
    add(&list2, &position, 10);
    bool result = isListEmpty(list1) &&
            !isListEmpty(list2);
    deleteList(list1);
    deleteList(list2);
    deletePosition(position);

    return result;
}