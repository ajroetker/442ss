#ifndef _STACK_H
#define _STACK_H

int *newStack(int size);
int isEmpty(int *S);
int size(int *S);
void push(int x, int *S);
int pop(int *S);
int top(int *S);
void output(int *S);

#endif
