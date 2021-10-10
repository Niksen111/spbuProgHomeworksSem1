#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

typedef struct
{
    char phone[30];
    char name[40];
}TelephoneDerectory;

int readBaseOfNumbers(char fileName[], TelephoneDerectory userDataBase[])
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }

}

void userInteraction(char fileName[])
{
    
    int numberOfOperation = -1;
    while (true)
    {
        printf("¬ведите номер нужной вам операции:\n");
        scanf("%d", &numberOfOperation);
        if (numberOfOperation == 0)
        {
            return;
        }
        else if (numberOfOperation == 1)
        {
            return;
        }
        else if (numberOfOperation == 2)
        {
            return;
        }
        else if (numberOfOperation == 3)
        {
            return;
        }
        else if (numberOfOperation == 4)
        {
            return;
        }
        else if (numberOfOperation == 5)
        {
            return;
        }
        else if (numberOfOperation == 6)
        {
            printf("0 - выйти\n1 - добавить запись(им€ и телефон)\n2 - распечатать все имеющиес€ записи\n3 - найти телефон по имени\n4 - найти им€ по телефону\n5 - сохранить текущие данные в файл\n6 - покзать список операций\n");
        }
        else
        {
            printf("¬ведено неверное значение\n");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    char fileName[40] = { 0 };
    printf("¬ведите им€ файла(телефонного справочника) формата .txt\n");
    scanf("%s", fileName);
    printf("0 - выйти\n1 - добавить запись(им€ и телефон)\n2 - распечатать все имеющиес€ записи\n3 - найти телефон по имени\n4 - найти им€ по телефону\n5 - сохранить текущие данные в файл\n6 - покзать список операций\n");
    userInteraction(fileName);
}