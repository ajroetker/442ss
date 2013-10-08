#ifndef _STACK_H
#define _STACK_H

typedef struct _stack {
    int size;
    int capacity;
    int *elements;
} stack;

stack *newStack(int capacity);
int isEmpty(stack *S);
int size(stack *S);
void push(int x, stack *S);
int pop(stack *S);
int top(stack *S);
void output(stack *S);

#endif
