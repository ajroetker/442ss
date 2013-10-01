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
queue *newQueue() {
  queue *Q = (queue *)malloc(sizeof(queue));
  Q->tail = NULL;
  Q->head = NULL;
  Q->size = 0;
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
  node *n = (node *)malloc(sizeof(node));
  n->data = x;
  n->next = NULL;
  if (Q->head == NULL) {
    Q->head = n;
  }
  else {
    Q->tail->next = n;
  }
  Q->tail = n;
  increaseQ(Q);
}


// dequeue
//
// Pops top value off of stack S,
// returns it.
//
int dequeue(queue *Q) {
  decreaseQ(Q);
  int x = Q->head->data;
  node *n = Q->head;
  Q->head = Q->head->next;
  free(n);
  return x;
}

// first
//
// Returns top value of stack S.
//
int front(queue *Q) {
  if (Q->head != NULL) {
    return Q->head->data;
  }
}

void outputQueue(queue *Q) {
  int i;
  if (isEmpty(Q)) {
    printf("[ ]");
  } else {
    node *n = Q->head;
    printf("[(%d)", n->data);
    n = n->next;
    while (n != NULL) {
      printf(" %d",n->data);
      n = n->next;
    }
    printf("]\n");
  }
}
