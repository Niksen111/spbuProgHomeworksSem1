#include "queueTests.h"
#include "queue.h"
#include <stdlib.h>

bool testCreateQueue()
{
    Queue* queue = createQueue();
    bool result = queue != NULL && dequeue(queue) == -1;
    deleteQueue(&queue);

    return result;
}

bool testEnqueue()
{
    Queue* queue = createQueue();
    bool result = queue != NULL && dequeue(queue) == -1;
    enqueue(queue, 8, 1);
    enqueue(queue, 4, 2);
    enqueue(queue, 8, 3);
    enqueue(queue, 11, 4);
    enqueue(queue, -1, 5);
    result = result && dequeue(queue) == 4
            && dequeue(queue) == 1
            && dequeue(queue) == 3
            && dequeue(queue) == 2
            && dequeue(queue) == 5
            && dequeue(queue) == -1;
    deleteQueue(&queue);

    return result;
}

bool testDequeue()
{
    Queue* queue = createQueue();
    bool result = queue != NULL && dequeue(queue) == -1;
    enqueue(queue, 8, 1);
    enqueue(queue, 4, 2);
    enqueue(queue, 8, 3);
    enqueue(queue, 11, 4);
    enqueue(queue, -1, 5);
    result = result && dequeue(queue) == 4
            && dequeue(queue) == 1
            && dequeue(queue) == 3
            && dequeue(queue) == 2
            && dequeue(queue) == 5
            && dequeue(queue) == -1;
    deleteQueue(&queue);

    return result;
}

bool testDeleteQueue()
{
    Queue* queue = createQueue();
    bool result = queue != NULL && dequeue(queue) == -1;
    deleteQueue(&queue);
    result = result && queue == NULL;

    return result;
}

bool testQueue()
{
    return testCreateQueue() && testEnqueue()
        && testDequeue() && testDeleteQueue();
}