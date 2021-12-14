#pragma once

typedef struct TwoDArray TwoDArray;

typedef struct SaddlePoint SaddlePoint;

TwoDArray* createArray(int n, int m);

void deleteArray(TwoDArray** twoDArray);

void fileInArray(TwoDArray* twoDArray);

void printTDArray(TwoDArray* twoDArray);

int getValueOfPoint(TwoDArray* twoDArray, int x, int y);

void findSaddlePoints(TwoDArray* twoDArray, int* x, int* y);