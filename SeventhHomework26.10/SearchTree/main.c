#include <stdio.h>
#include "searchTreeTests.h"
#include "searchTree.h"

void printOperations()
{
    printf("0 - выйти\n");
    printf("1 - добавить значение в словарь\n");
    printf("2 - получить значение по заданному ключу\n");
    printf("3 - проверить наличие ключа в словаре\n");
    printf("4 - удалить заданную ячейку по ключу\n");
    printf("5 - распечатать список доступных операций\n");
}

void interactWithUser()
{
    TreeRoot* myTree = createTreeRoot();
    printOperations();
    while (true)
    {
        int operation = 0;
        printf("Введите номер нужной вам операции:\n");
        printf("(введите 5 если хотите увидеть список операций)\n");
        scanf("%d", &operation);
        switch (operation)
        {
            case 0:
                return;
            case 1:
            {
                int key = 0;
                char value[10010] = { 0 };
                printf("Введите ключ\n");
                scanf("%d", &key);
                printf("Введите значение (не более 10000 символов)\n");
                scanf("%s", value);
                addTreeNode(myTree, key, value);
                break;
            }
            case 2:
            {
                int key = 0;
                printf("Введите ключ\n");
                scanf("%d", &key);
                char* value = findValue(myTree, key);
                if (value == NULL)
                {
                    printf("Запись не найдена.\n");
                }
                else
                {
                    printf("Искомое значение:\n");
                    printf("%s\n", value);
                }
                break;
            }
            case 3:
            {
                int key = 0;
                printf("Введите ключ\n");
                scanf("%d", &key);
                if (isKeyInTree(myTree, key))
                {
                    printf("Данный ключ присутствует в словаре.\n");
                }
                else
                {
                    printf("Данный ключ отсутствует в словаре.\n");
                }
                break;
            }
            case 4:
            {
                int key = 0;
                printf("Введите ключ\n");
                scanf("%d", &key);
                removeEntry(&myTree, key);
                break;
            }
            case 5:
            {
                printOperations();
                break;
            }
            default:
                printf("Введена неверная операция\n");
        }
    }
}

int main() {
    if (!testSearchTree())
    {
        printf("Tests failed(\n");
        return -1;
    }
    interactWithUser();
    return 0;
}
