#pragma once

// queue structure
typedef struct Queue Queue;

// creates a queue of minimum size
Queue* createQueue();

// adds an item to the queue by key
int enqueue(Queue* queue, int key, int value);

// removes the priority item and returns it
// otherwise returns -1
int dequeue(Queue* queue);

// removes the queue
void deleteQueue(Queue** queue);