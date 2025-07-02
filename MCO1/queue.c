#include "queue.h"

void createQueue(Queue *queue){
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
}

bool enqueue(Queue *queue, str256 token){
    bool status = false;
    if (queue->size < MAX)
    {
        strcpy(queue->items[queue->tail], token);
        queue->tail = (queue->tail + 1) % MAX;
        queue->size++;
        status = !status;
    }
    return status;   
}

bool dequeue(Queue *queue, str256 token){
    bool status = false;
    if (queue->size > 0)
    {
        strcpy(token, queue->items[queue->head]);
        queue->head = (queue->head + 1) % MAX;
        queue->size--;
        status = !status;
    }
    return status; 
}

bool queueHead(Queue *queue, str256 token){
    bool status = false;
    if (queue->size > 0)
    {
        strcpy(token, queue->items[queue->head]);
        status = !status;
    }
    return status;
}

bool queueTail(Queue *queue, str256 token){
    bool status = false;
    int lastValidIndex;
    if (queue->size > 0)
    {
        lastValidIndex = (queue->tail - 1 + MAX) % MAX;
        strcpy(token, queue->items[lastValidIndex]);
        status = !status;
    }
    return status;
}

bool queueEmpty(Queue *queue){
    bool status = false;
    if (queue->size == 0)
    {
        status = !status;
    }
    return status;
}

bool queueFull(Queue *queue){
    bool status = false;
    if (queue->size == MAX)
    {
        status = !status;
    }
    return status;
}