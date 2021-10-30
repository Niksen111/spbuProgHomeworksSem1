#include <stdio.h>
#include "sortedList.h"

void printListOfOperations()
{
    printf("0 – выйти\n");
    printf("1 – добавить значение в сортированный список\n");
    printf("2 – удалить значение из списка\n");
    printf("3 – распечатать список\n");
    printf("4 - распечатать список операций\n");
}

int interactWithUser()
{
    SortedList* myList = createSortedList();
    int currentOperation = -1;
    while (currentOperation != 0)
    {
        printf("Введите нужную вам команду:\n");
        printf("(Введите 4 если хотите увидеть список команд)\n");
        scanf("%d", &currentOperation);
        if (currentOperation == 1)
        {
            Value addedValue = 0;
            printf("Введите значение добавляемого элемента:\n");
            scanf("%d", &addedValue);
            if (push(&myList, addedValue) != 0)
            {
                printf("Недостаточно памяти, для");
                printf("добавления нового элемента.\n");
                return -1;
            }
        }
        else if (currentOperation == 2)
        {
            Value deletedValue = 0;
            printf("Введите значение удаляемого элемента:\n");
            scanf("%d", &deletedValue);
            if (removeTheItem(&myList, deletedValue) == -1)
            {
                printf("Данного элемента нет в списке.\n");
            }
        }
        else if (currentOperation == 3)
        {
            printSortedList(&myList);
            if (sortedListIsEmpty(&myList))
            {
                printf("Список пуст.\n");
            }
        }
        else if (currentOperation == 4)
        {
            printListOfOperations();
        }
        else if (currentOperation != 0)
        {
            printf("Введена неизвестная операция.\n");
        }
    }
}

int main() {
    printListOfOperations();
    interactWithUser();
    return 0;
}
