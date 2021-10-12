#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char phone[20];
    char name[30];
}TelephoneDerectory;

bool checkThatAnArraysAreIdentical(const char firstArray[],
    const char secondArray[], const int lengthOfArrays)
{
    for (int i = 0; i < lengthOfArrays; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
}

int writeTelephoneDerectoyIntoFile(const char fileName[], 
    const TelephoneDerectory userDataBase[], const int lengthOfBase)
{
    FILE* file = fopen(fileName, "w");
    for (int i = 0; i < lengthOfBase; ++i)
    {
        fprintf_s(file, "%s", userDataBase[i].phone);
        fprintf(file, ' ');
        fprintf_s(file, "%s", userDataBase[i].name);
        fprintf(file, '\n');
    }
    fclose(file);
    return 0;
}

int findName(char desiredPhone[], const TelephoneDerectory userDataBase[], 
    const int lengthOfBase, char contactName[])
{
    for (int i = 0; i < lengthOfBase; ++i)
    {
        if (checkThatAnArraysAreIdentical(userDataBase[i].phone, desiredPhone, 30))
        {
            strcpy(contactName, userDataBase[i].phone);
            return 0;
        }
    }
    return -1;
}

void printCharArray(const char theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%c", theArray[i]);
    }
}

int readTelephoneDerectoryFromFile(const char fileName[], 
    TelephoneDerectory userDataBase[], int *lengthOfBase)
{
    *lengthOfBase = 0;
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }
    char symbol = '\0';
    
    while (true)
    {
        for (int i = 0; i < 20; ++i)
        {
            if ((symbol = fgetc(file)) != EOF)
            {
                userDataBase[*lengthOfBase].phone[i] = symbol;
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
                userDataBase[*lengthOfBase].name[i] = symbol;
            }
            else
            {
                fclose(file);
                return 0;
            }
        }
        ++* lengthOfBase;
        if ((symbol = fgetc(file)) == EOF)
        {
            fclose(file);
            return 0;
        }
    }
}

void fillArrayWithSpaces(char theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        theArray[i] = ' ';
    }
}

void printBase(const TelephoneDerectory userDataBase[], const int lengthOfBase)
{
    for (int i = 0; i < lengthOfBase; ++i)
    {
        printCharArray(userDataBase[i].phone, 20);
        printf(" ");
        printCharArray(userDataBase[i].name, 30);
        printf("\n");
    }
}

void stringCopy(char mainArray[], char secondArray[])
{
    for (int i = 0; secondArray[i] != '\0'; ++i)
    {
        mainArray[i] = secondArray[i];
    }
}

int addEntry(TelephoneDerectory userDataBase[], int *lengthOfBase, const char phone[], const char name[])
{
    stringCopy(userDataBase[*lengthOfBase].phone, phone);
    stringCopy(userDataBase[*lengthOfBase].name, name);
    ++*lengthOfBase;
}

void userInteraction(const char fileName[])
{
    TelephoneDerectory userDataBase[100] = { 0 };
    int lengthOfBase = 0;

    readTelephoneDerectoryFromFile(fileName, userDataBase, &lengthOfBase);
    int numberOfOperation = -1;
    while (true)
    {
        printf("Введите номер нужной вам операции:\n");
        scanf("%d", &numberOfOperation);
        if (numberOfOperation == 0)
        {
            return;
        }
        else if (numberOfOperation == 1)
        {
            fillArrayWithSpaces(userDataBase[lengthOfBase].phone, 20);
            fillArrayWithSpaces(userDataBase[lengthOfBase].name, 30);
            char phoneNew[20] = { 0 };
            char nameNew[30] = { 0 };
            printf("Введите номер телефона (не более 20 символов):\n");
            scanf_s(" %[^\n]", phoneNew, 20);
            printf("Ввеидите имя контакта (не более 30 символов):\n");
            scanf_s(" %[^\n]", nameNew, 30);
            addEntry(userDataBase, &lengthOfBase, phoneNew, nameNew);
        }
        else if (numberOfOperation == 2)
        {
            printBase(userDataBase, lengthOfBase);
        }
        else if (numberOfOperation == 3)
        {
            
        }
        else if (numberOfOperation == 4)
        {
            char desiredPhone[20] = { 0 };
            fillArrayWithSpaces(desiredPhone, 20);
            printf("Введите искомый номер телефона:\n");
            scanf("%s", desiredPhone);
            char contactName[30] = { 0 };
            if (findName(desiredPhone, userDataBase, lengthOfBase, contactName) == 0)
            {
                printf("Контакт не найден.\n");
            }
            else
            {
                printf("Искомый контакт:\n%s\n", contactName);
            }
        }
        else if (numberOfOperation == 5)
        {
            writeTelephoneDerectoyIntoFile(fileName, userDataBase, lengthOfBase);
        }
        else if (numberOfOperation == 6)
        {
            printf("0 - выйти\n1 - добавить запись(имя и телефон)\n2 - распечатать все имеющиеся записи\n3 - найти телефон по имени\n4 - найти имя по телефону\n5 - сохранить текущие данные в файл\n6 - покзать список операций\n");
        }
        else
        {
            printf("Введено неверное значение\n");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    /*char fileName[40] = { 0 };
    printf("Введите имя файла(телефонного справочника) формата .txt\n");
    scanf("%s", fileName);*/
    printf("0 - выйти\n1 - добавить запись(имя и телефон)\n2 - распечатать все имеющиеся записи\n3 - найти телефон по имени\n4 - найти имя по телефону\n5 - сохранить текущие данные в файл\n6 - покзать список операций\n");
    userInteraction("directory.txt");
}