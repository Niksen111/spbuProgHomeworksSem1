#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

typedef struct
{
    char phone[20];
    char name[30];
}TelephoneDerectory;

int readBaseOfNumbers(char fileName[], TelephoneDerectory userDataBase[])
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -1;
    }
    char symbol = '\0';
    int currentNumber = 0;
    while (true)
    {
        for (int i = 0; i < 20; ++i)
        {
            if ((symbol = fgetc(file)) != EOF)
            {
                *userDataBase[currentNumber].phone = symbol;
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
                *userDataBase[currentNumber].name = symbol;
            }
            else
            {
                fclose(file);
                return 0;
            }
        }
    }
}

void userInteraction(char fileName[])
{
    
    int numberOfOperation = -1;
    while (true)
    {
        printf("������� ����� ������ ��� ��������:\n");
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
            printf("0 - �����\n1 - �������� ������(��� � �������)\n2 - ����������� ��� ��������� ������\n3 - ����� ������� �� �����\n4 - ����� ��� �� ��������\n5 - ��������� ������� ������ � ����\n6 - ������� ������ ��������\n");
        }
        else
        {
            printf("������� �������� ��������\n");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    char fileName[40] = { 0 };
    printf("������� ��� �����(����������� �����������) ������� .txt\n");
    scanf("%s", fileName);
    printf("0 - �����\n1 - �������� ������(��� � �������)\n2 - ����������� ��� ��������� ������\n3 - ����� ������� �� �����\n4 - ����� ��� �� ��������\n5 - ��������� ������� ������ � ����\n6 - ������� ������ ��������\n");
    userInteraction(fileName);
}