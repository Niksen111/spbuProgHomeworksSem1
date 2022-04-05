#include <stdlib.h>
#include "queue.h"

typedef struct Pair
{
    int key;
    int value;
} Pair;

typedef struct Queue
{
    Pair** pairArray;
    int lengthOfArray;
    int filledCells;
};

void swap(int* x1, int* x2)
{
    *x1 ^= *x2;
    *x2 ^= *x1;
    *x1 ^= *x2;
}

void swapPairs(Pair* pair1, Pair* pair2)
{
    swap(&pair1->value, &pair2->value);
    swap(&pair1->key, &pair2->key);
}

void changePair(Pair* pair, int key, int value)
{
    pair->key = key;
    pair->value = value;
}

void deletePairArray(Pair*** pairArray, int lengthOfArray)
{
    for (int i = 0; i < lengthOfArray; ++i)
    {
        free((*pairArray)[i]);
    }
    free(*pairArray);
}

void increaseQueue(Queue* queue)
{
    int newLength = queue->lengthOfArray * 2;
    Pair** newArray = calloc(newLength, sizeof(Pair*));
    for (int i = 0; i < newLength; ++i)
    {
        newArray[i] = calloc(1, sizeof(Pair));
        newArray[i]->value = -1;
    }
    for (int i = 0; i < queue->lengthOfArray; ++i)
    {
        swapPairs(newArray[i], queue->pairArray[i]);
    }
    deletePairArray(&queue->pairArray, queue->lengthOfArray);
    queue->pairArray = newArray;
    queue->lengthOfArray = newLength;
}

Queue* createQueue()
{
    Queue* newQueue = calloc(1, sizeof(Queue));
    Pair** pairArray = calloc(10, sizeof(Pair*));
    for (int i = 0; i < 10; ++i)
    {
        pairArray[i] = calloc(1, sizeof(Pair));
        pairArray[i]->value = -1;
    }
    newQueue->pairArray = pairArray;
    newQueue->lengthOfArray = 10;
    return newQueue;
}

void fixHeapInsert(Queue* queue, int index)
{
    if (index == 0)
    {
        return;
    }
    int x = 1;
    if (index % 2 == 0)
    {
        ++x;
    }
    int parentIndex = (index - x) / 2;
    if (queue->pairArray[index]->key <= queue->pairArray[parentIndex]->key)
    {
        return;
    }
    swapPairs(queue->pairArray[index], queue->pairArray[parentIndex]);
    fixHeapInsert(queue, parentIndex);
}

void fixHeapExtraction(Queue* queue, int index)
{
    int sonIndex = index * 2 + 2;
    if (sonIndex <= 0 || sonIndex > queue->filledCells)
    {
        return;
    }
    if (sonIndex == queue->filledCells)
    {
        sonIndex -= 1;
        swapPairs(queue->pairArray[index], queue->pairArray[sonIndex]);
        fixHeapInsert(queue, sonIndex);
        return;
    }
    if (queue->pairArray[index]->key > queue->pairArray[sonIndex]->key && queue->pairArray[index]->key > queue->pairArray[sonIndex - 1]->key)
    {
        return;
    }
    if (queue->pairArray[sonIndex - 1]->key >= queue->pairArray[sonIndex]->key)
    {
        sonIndex -= 1;
    }
    swapPairs(queue->pairArray[index], queue->pairArray[sonIndex]);
    fixHeapExtraction(queue, sonIndex);
}

int enqueue(Queue* queue, int key, int value)
{
    if (queue == NULL)
    {
        return -1;
    }
    if (queue->lengthOfArray - queue->filledCells < 1)
    {
        increaseQueue(queue);
    }
    changePair(queue->pairArray[queue->filledCells], key, value);
    fixHeapInsert(queue, queue->filledCells);
    ++queue->filledCells;
}

int dequeue(Queue* queue)
{
    if (queue == NULL || queue->lengthOfArray == 0 || queue->filledCells == 0)
    {
        return -1;
    }
    int returnedValue = queue->pairArray[0]->value;
    swapPairs(queue->pairArray[0], queue->pairArray[queue->filledCells - 1]);
    queue->pairArray[queue->filledCells - 1]->key = 0;
    queue->pairArray[queue->filledCells - 1]->value = -1;
    --queue->filledCells;
    fixHeapExtraction(queue, 0);
    return returnedValue;
}

void deleteQueue(Queue** queue)
{
    deletePairArray(&(*queue)->pairArray, (*queue)->lengthOfArray);
    free(*queue);
    *queue = NULL;
}