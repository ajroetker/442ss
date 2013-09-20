#ifndef _CONTAINER_H
#define _CONTAINER_H

typedef struct {
    int size;
    int capacity;
    int *elements;
} container;

typedef struct {
    container C;
    int *index;
} queue;

container *newContainer(int capacity);
int isEmpty(container *C);
void decrease(container *C);
void increase(container *C);
int size(container *C);
void output(container *C);

#endif
