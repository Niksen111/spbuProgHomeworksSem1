#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char phone[20];
    char name[30];
}TelephoneDerectory;

void printCharArray(const char theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%c", theArray[i]);
    }
}

int readTelephoneDerectoryFromFile(const char fileName[], TelephoneDerectory userDataBase[], int *lengthOfBase)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }
    char symbol = '\0';
    *lengthOfBase = 1;
    while (true)
    {
        for (int i = 0; i < 20; ++i)
        {
            if ((symbol = fgetc(file)) != EOF)
            {
                userDataBase[*lengthOfBase - 1].phone[i] = symbol;
            }
            else
            {
                fclose(file);
                return 0;
            }
        }
        if ((symbol = fgetc(file)) == EOF)
        {
            fclose(file);
            return 0;
        }
        for (int i = 0; i < 30; ++i)
        {
            if ((symbol = fgetc(file)) != EOF)
            {
                userDataBase[*lengthOfBase - 1].name[i] = symbol;
            }
            else
            {
                fclose(file);
                return 0;
            }
        }
        if ((symbol = fgetc(file)) == EOF)
        {
            fclose(file);
            return 0;
        }
        ++*lengthOfBase;
    }
}

void fillArrayWithSpaces(char theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        theArray[i] = ' ';
    }
}

void printBase(TelephoneDerectory userDataBase[], int lengthOfBase)
{
    for (int i = 0; i < lengthOfBase; ++i)
    {
        printCharArray(userDataBase[i].phone, 20);
        printf(" ");
        printCharArray(userDataBase[i].name, 30);
        printf("\n");
    }
}

int addEntry(TelephoneDerectory userDataBase[], int *lengthOfBase, char phone[], char name[])
{
    strcpy(userDataBase[*lengthOfBase].phone, phone);
    strcpy(userDataBase[*lengthOfBase].name, name);
    ++*lengthOfBase;
}

void userInteraction(const char fileName[])
{
    TelephoneDerectory baseOfNumbers[100] = { 0 };
    int lengthOfBase = 0;

    readTelephoneDerectoryFromFile(fileName, baseOfNumbers, &lengthOfBase);
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
            fillArrayWithSpaces(baseOfNumbers[lengthOfBase].phone, 20);
            fillArrayWithSpaces(baseOfNumbers[lengthOfBase].name, 30);
            char phone[20] = { 0 };
            char name[30] = { 0 };
            printf("¬ведите номер телефона (не более 20 символов):\n");
            scanf_s(" %[^\n]%*s", phone, 20);
            printf("¬веидите им€ контакта (не более 30 символов):\n");
            scanf_s(" %[^\n]%*s", name, 30);
            addEntry(baseOfNumbers, &lengthOfBase, phone, name);
        }
        else if (numberOfOperation == 2)
        {
            printBase(baseOfNumbers, lengthOfBase);
        }
        else if (numberOfOperation == 3)
        {
            
        }
        else if (numberOfOperation == 4)
        {
            
        }
        else if (numberOfOperation == 5)
        {
            
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
    /*char fileName[40] = { 0 };
    printf("¬ведите им€ файла(телефонного справочника) формата .txt\n");
    scanf("%s", fileName);*/
    printf("0 - выйти\n1 - добавить запись(им€ и телефон)\n2 - распечатать все имеющиес€ записи\n3 - найти телефон по имени\n4 - найти им€ по телефону\n5 - сохранить текущие данные в файл\n6 - покзать список операций\n");
    userInteraction("directory.txt");
}