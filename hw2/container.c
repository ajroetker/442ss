#include <stdio.h>
#include <stdlib.h>
#include "container.h"

// isEmpty
//
// Checks whether the stack is empty.
int isEmpty(container *C) {
  return (size(C) == 0);
}

// size
//
// Returns the number of elements on the stack.
int size(container *C) {
  return C->size;
}

// increase, decrease
//
// Two stack size helper functions.
void decrease(container *C) {
  C->size--;
}
void increase(container *C) {
  C->size++;
}

// newQueue
//
// Creates and returns a new queue with the
// given capacity. Its representation is an
// array of integers, potential elements to
// be stored in the stack.  The array item
// at -1 holds the number of elements stored
// on the queue, initially 0.
//
queue *newQueue(int capacity) {
  queue *Q = (queue *)malloc(sizeof(queue));
  container *cont_ptr = (container *) Q;
  cont_ptr->capacity = capacity;
  cont_ptr->size = 0;
  cont_ptr->elements = (int *)malloc((capacity)*sizeof(int));
  Q->index = 0;
  return Q;
}

// enqueue
//
void enqueue(int x, queue* Q) {
  container *cont_ptr = (container *) Q;
  if (cont_ptr->size == cont_ptr->capacity) {
    printf("QueueOverflowError: Tried to add too many items to the queue!\n");
  }
  else {
    Q->elements[(Q->index + size((container *)Q)) % Q->capacity] = x;
    increase(Q);
  }
}


// dequeue
//
// Pops top value off of stack S,
// returns it.
//
int dequeue(queue *Q) {
  decrease(Q);
  if (size(Q) > 0) {
    Q->index = (Q->index + 1) % Q->capacity;
    return Q->elements[(Q->capacity + Q->index - 1) % Q->capacity ];
  }
  else {
    return Q->elements[Q->index];
  }
}

// first
//
// Returns top value of stack S.
//
int front(queue *Q) {
  return Q->elements[Q->index];
}

void output(queue *Q) {
  int i;
  if (isEmpty(Q)) {
    printf("[ ]");
  } else {
    printf("[");
    printf("(%d)",front(Q));
    for (i=1; i<size(Q); i++) {
      printf(" %d",Q->elements[(Q->index + i) % Q->capacity]);
    }
    printf("]\n");
  }
}
