#include <stdlib.h>
#include <stdio.h>
#include "twoDimensionalArray.h"

typedef struct TwoDArray
{
    int** twoDArray;
    int row;
    int column;
} TwoDArray;

TwoDArray* createArray(int row, int column)
{
    TwoDArray* twoDArray = calloc(1, sizeof(TwoDArray));
    twoDArray->twoDArray = calloc(column, sizeof(int*));
    for (int i = 0; i < column; ++i)
    {
        twoDArray->twoDArray[i] = calloc(row, sizeof(int));
    }
    return twoDArray;
}

void deleteArray(TwoDArray** twoDArray)
{
    for (int i = 0; i < (*twoDArray)->column; ++i)
    {
        free((*twoDArray)->twoDArray[i]);
    }
    free((*twoDArray)->twoDArray);
    free(*twoDArray);
}

void fileInArray(TwoDArray* twoDArray)
{
    for (int i = 0; i < twoDArray->column; ++i)
    {
        for (int j = 0; j < twoDArray->row; ++j)
        {
            int number = 0;
            scanf("%d", &number);
            twoDArray->twoDArray[i][j] = number;
        }
    }
}

void printTDArray(TwoDArray* twoDArray)
{
    for (int i = 0; i < twoDArray->column; ++i)
    {
        for (int j = 0; j < twoDArray->row; ++j)
        {
            printf("%d ", twoDArray->twoDArray[i][j]);
        }
        printf("\n");
    }
}

int getValueOfPoint(TwoDArray* twoDArray, int x, int y)
{
    return twoDArray->twoDArray[y][x];
}

void findSaddlePoints(TwoDArray* twoDArray, int* x, int* y)
{
    int* xCoordinates = calloc(twoDArray->column, sizeof(int));
    int* yCoordinates = calloc(twoDArray->column, sizeof(int));
    int index = 0;
    for (int i = 0; i < twoDArray->column; ++i)
    {
        int minInRow = twoDArray->twoDArray[i][0];
        int x1 = 0;
        int y1 = i;
        for (int j = 1; j < twoDArray->row; ++j)
        {
            if (twoDArray->twoDArray[i][j] < minInRow)
            {
                x1 = j;
                minInRow = twoDArray->twoDArray[i][j];
            }
        }
        xCoordinates[index] = x1;
        yCoordinates[index] = y1;
        ++index;
    }
    for (int j = 0; j < twoDArray->row; ++j)
    {
        for (int i = 0; i < twoDArray->column; ++i)
        {

        }
        
    }
}