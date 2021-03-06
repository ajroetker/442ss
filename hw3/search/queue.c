#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "node.h"

// newQueue
//
// Creates and returns a new queue with the
// given capacity. Its representation is an
// array of integers, potential elements to
// be stored in the stack.  The array item
// at -1 holds the number of elements stored
// on the queue, initially 0.
//
queue *newQueue(int size) {
  queue *Q = (queue *)malloc(sizeof(queue));
  Q->elements = (int *)malloc(sizeof(int)*size);
  Q->head = 0;
  Q->size = 0;
  Q->capacity = size;
  return Q;
}

// isEmpty
//
// Checks whether the stack is empty.
int isEmptyQueue(queue *Q) {
  return (sizeQueue(Q) == 0);
}

// size
//
// Returns the number of elements on the stack.
int sizeQueue(queue *Q) {
  return Q->size;
}

// increase, decrease
//
// Two stack size helper functions.
void decreaseQ(queue *Q) {
  Q->size--;
}
void increaseQ(queue *Q) {
  Q->size++;
}

// enqueue
//
// Pushes x onto stack S.
//
void enqueue(int x, queue* Q) {
  if(Q->size == Q->capacity){
    printf("Queue is full!");
  }
  else {
    Q->elements[(Q->head + Q->size) % Q->capacity] = x;
    increaseQ(Q);
  }
}


// dequeue
//
// Pops top value off of stack S,
// returns it.
//
int dequeue(queue *Q) {
  decreaseQ(Q);
  int x = Q->elements[Q->head];
  Q->head = (Q->head + 1) % Q->capacity;
  return x;
}

// first
//
// Returns top value of stack S.
//
int front(queue *Q) {
  if (Q->size > 0) {
    return Q->elements[Q->head];
  }
}

void outputQueue(queue *Q) {
  int i;
  if (isEmptyQueue(Q)) {
    printf("[ ]");
  } else {
    printf("[(%d)", Q->elements[Q->head]);
    int i = Q->head+1;
    int j = 1;
    while (j < Q->size) {
      printf(" %d", Q->elements[i]);
      i++;
      j++;
    }
    printf("]\n");
  }
}
