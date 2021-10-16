#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char phone[21];
    char name[31];
} TelephoneDirectory;

void printListOfOperations()
{
    printf("    0 - выйти\n");
    printf("    1 - добавить запись (имя и телефон)\n");
    printf("    2 - распечатать все имеющиеся записи\n");
    printf("    3 - найти телефон по имени\n");
    printf("    4 - найти имя по телефону\n");
    printf("    5 - сохранить текущие данные в файл\n");
    printf("    6 - показать список операций");
}

bool checkThatTheArraysAreIdentical(const char firstArray[],
    const char secondArray[], const int lengthOfArrays)
{
    for (int i = 0; firstArray[i] != '\0'; ++i)
    {
        if (firstArray[i] != secondArray[i])
        {
            return false;
        }
    }
    return true;
}

int writeTelephoneDerectoyIntoFile(const char fileName[], 
    const TelephoneDirectory userDataBase[], const int lengthOfBase)
{
    FILE* file = fopen(fileName, "w");
    for (int i = 0; i < lengthOfBase; ++i)
    {
        fwrite(userDataBase[i].phone, sizeof(char), 20, file);
        fwrite(" ", sizeof(char), 1, file);
        fwrite(userDataBase[i].name, sizeof(char), 30, file);
        fwrite("\n", sizeof(char), 1, file);
    }
    fclose(file);
    return 0;
}

void stringCopy(char mainArray[], const char secondArray[])
{
    for (int i = 0; secondArray[i] != '\0'; ++i)
    {
        mainArray[i] = secondArray[i];
    }
}

void printCharArray(const char theArray[], const int lengthOfTheArray)
{
    for (int i = 0; i < lengthOfTheArray; ++i)
    {
        printf("%c", theArray[i]);
    }
}

int findName(char desiredPhone[], const TelephoneDirectory userDataBase[],
    const int lengthOfBase, char contactName[])
{
    for (int i = 0; i < lengthOfBase; ++i)
    {
        if (checkThatTheArraysAreIdentical(userDataBase[i].phone, desiredPhone, 30))
        {
            stringCopy(contactName, userDataBase[i].phone);
            return 0;
        }
    }
    return -1;
}

int readTelephoneDirectoryFromFile(const char fileName[],
                                   TelephoneDirectory userDataBase[], int *lengthOfBase)
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
        userDataBase[*lengthOfBase].phone[20] = '\0';
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
        userDataBase[*lengthOfBase].name[30] = '\0';
        ++*lengthOfBase;
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

void printBase(const TelephoneDirectory userDataBase[], const int lengthOfBase)
{
    for (int i = 0; i < lengthOfBase; ++i)
    {
        printCharArray(userDataBase[i].phone, 20);
        printf(" ");
        printCharArray(userDataBase[i].name, 30);
        printf("\n");
    }
}

int addEntry(TelephoneDirectory userDataBase[], int *lengthOfBase, const char phone[], const char name[])
{
    strcpy(userDataBase[*lengthOfBase].phone, phone);
    //stringCopy(userDataBase[*lengthOfBase].phone, phone);
    strcpy(userDataBase[*lengthOfBase].name, name);
    //stringCopy(userDataBase[*lengthOfBase].name, name);
    ++*lengthOfBase;
    return 0;
}

void userInteraction(const char fileName[])
{
    TelephoneDirectory userDataBase[100] = { 0 };
    int lengthOfBase = 0;

    readTelephoneDirectoryFromFile(fileName, userDataBase, &lengthOfBase);
    int numberOfOperation = -1;
    while (true)
    {
        printf("\nВведите номер нужной вам операции:\n"
               "(введите 6 если хотите напомнить список операций)\n");
        scanf("%d", &numberOfOperation);
        printf("\n");
        if (numberOfOperation == 0)// выйти
        {
            return;
        }
        else if (numberOfOperation == 1)// добавить запись (имя и телефон)
        {
            fillArrayWithSpaces(userDataBase[lengthOfBase].phone, 20);
            userDataBase[lengthOfBase].phone[20] = '\0';
            fillArrayWithSpaces(userDataBase[lengthOfBase].name, 30);
            userDataBase[lengthOfBase].name[30] = '\0';
            char phoneNew[20] = { 0 };
            char nameNew[30] = { 0 };
            printf("Введите номер телефона (не более 20 символов):\n");
            scanf(" %[^\n]", phoneNew);
            printf("Введите имя контакта (не более 30 символов):\n");
            scanf(" %[^\n]", nameNew);
            addEntry(userDataBase, &lengthOfBase, phoneNew, nameNew);
        }
        else if (numberOfOperation == 2)// распечатать все имеющиеся записи
        {
            printBase(userDataBase, lengthOfBase);
        }
        else if (numberOfOperation == 3) // найти телефон по имени
        {
            
        }
        else if (numberOfOperation == 4) // найти имя по телефону
        {
            char desiredPhone[20] = { 0 };
            fillArrayWithSpaces(desiredPhone, 20);
            printf("Введите искомый номер телефона:\n");
            scanf(" %[^\n]", desiredPhone);
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
        else if (numberOfOperation == 5) // сохранить текущие данные в файл
        {
            writeTelephoneDerectoyIntoFile(fileName, userDataBase, lengthOfBase);
        }
        else if (numberOfOperation == 6) // показать список операций
        {
            printListOfOperations();
        }
        else
        {
            printf("Введён неверный номер операции.\n");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    printListOfOperations();
    userInteraction("directory.txt");
}