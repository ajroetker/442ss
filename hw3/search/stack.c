#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// newStack
//
// Creates and returns a new stack with the 
// given capacity. Its representation is an
// array of integers, potential elements to
// be stored in the stack.  The array item 
// at -1 holds the number of elements stored
// on the stack, initially 0.
//
stack *newStack(int capacity) {
  stack *S = (stack *)malloc(sizeof(stack));
  S->capacity = capacity;
  S->size = 0;
  S->elements = (int *)malloc((capacity)*sizeof(int));
  return S;  // start at first element, 0th holds size
}

// isEmpty
//
// Checks whether the stack is empty.
int isEmpty(stack *S) {
  return (size(S) == 0);
}

// size
//
// Returns the number of elements on the stack.
int size(stack *S) {
  return S->size;
}

// increase, decrease
//
// Two stack size helper functions.
void decrease(stack *S) {
  S->size--;
}
void increase(stack *S) {
  S->size++;
}

// push
//
// Pushes x onto stack S.
//
void push(int x, stack *S) {
  S->elements[size(S)] = x;
  increase(S);
}


// pop
//
// Pops top value off of stack S,
// returns it.
//
int pop(stack *S) {
  decrease(S);
  return S->elements[size(S)];
}

// top
//
// Returns top value of stack S.
//
int top(stack *S) {
  return S->elements[size(S)-1];
}

void output(stack *S) {
  int i;
  if (isEmpty(S)) {
    printf("[ ]");
  } else {
    printf("[");
    for (i=0; i<size(S)-1; i++) {
      printf("%d ",S->elements[i]);
    }
    printf("(%d)]\n",top(S));
  }
}
