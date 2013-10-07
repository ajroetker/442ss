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
int *newStack(int capacity) {
  int *S = (int *)malloc((capacity+1)*sizeof(int));
  S[0] = 0;
  return &S[1];  // start at first element, 0th holds size
}

// isEmpty
//
// Checks whether the stack is empty.
int isEmpty(int *S) {
  return (size(S) == 0);
}

// size
//
// Returns the number of elements on the stack.
int size(int *S) {
  return S[-1];
}
 
// increase, decrease
//
// Two stack size helper functions.
void decrease(int *S) {
  S[-1]--;
}
void increase(int *S) {
  S[-1]++;
}
 
// push
//
// Pushes x onto stack S.
//
void push(int x, int *S) {
  S[size(S)] = x;
  increase(S);
}


// pop
//
// Pops top value off of stack S,
// returns it.
//
int pop(int *S) {
  decrease(S);
  return S[size(S)];
}

// top
//
// Returns top value of stack S.
//
int top(int *S) {
  return S[size(S)-1];
}

void output(int *S) {
  int i;
  if (isEmpty(S)) {
    printf("[ ]");
  } else {
    printf("[");
    for (i=0; i<size(S)-1; i++) {
      printf("%d ",S[i]);
    }
    printf("(%d)\n",top(S));
  }
}
