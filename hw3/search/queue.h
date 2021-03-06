#include "node.h"
#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct _queue {
    int* elements;
    int tail;
    int head;
    int size;
    int capacity;
} queue;

queue *newQueue(int size);
int isEmptyQueue(queue *Q);
int sizeQueue(queue *Q);
void enqueue(int x, queue *Q);
int dequeue(queue *Q);
int front(queue *Q);
void outputQueue(queue *Q);

#endif
