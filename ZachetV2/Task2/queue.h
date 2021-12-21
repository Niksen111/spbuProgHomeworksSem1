#pragma once

typedef struct Queue Queue;

Queue* createQueue();

int enqueue(Queue* queue, int key, int value);

int dequeue(Queue* queue);

void deleteQueue(Queue** queue);