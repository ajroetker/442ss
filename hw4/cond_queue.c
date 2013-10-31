#include <pthread.h>
#include <stdlib.h>
#include "csapp.h"
#include "cond_queue.h"

queue *queue_new(int c) {
  queue *q = (queue *)malloc(sizeof(queue));
  q->capacity = c;
  q->elements = (T *)malloc(c*sizeof(T));
  q->head = 0;
  q->tail = 0;
  q->items = 0;
  q->slots = c;
  pthread_mutex_init(&q->mutex,NULL);
  pthread_cond_init(&q->has_items,NULL);
  pthread_cond_init(&q->has_slots,NULL);
  return q;
}

int queue_is_empty(queue *q) {
  int is_empty;
  pthread_mutex_lock(&q->mutex);
  is_empty = (q->items == 0);
  pthread_mutex_unlock(&q->mutex);
  return is_empty;
}

int queue_is_full(queue *q) {
  int is_full;
  pthread_mutex_lock(&q->mutex);
  is_full = (q->slots == 0);
  pthread_mutex_unlock(&q->mutex);
  return is_full;
}

void enqueue(T x, queue *q) {
  pthread_mutex_lock(&q->mutex);
  // wait until slot is available
  while (q->slots == 0) {
    pthread_cond_wait(&q->has_slots,&q->mutex);
  }
  q->elements[q->tail] = x;
  q->tail = (q->tail + 1) % q->capacity;
  q->items++;
  q->slots--;
  pthread_cond_signal(&q->has_items);
  pthread_mutex_unlock(&q->mutex);
}

T dequeue(queue *q) {
  int x;
  pthread_mutex_lock(&q->mutex);
  // wait until item is available
  while (q->items == 0) {
    pthread_cond_wait(&q->has_items,&q->mutex);
  }
  x = q->elements[q->head];
  q->head = (q->head + 1) % q->capacity;
  q->items--;
  q->slots++;
  pthread_cond_signal(&q->has_slots);
  pthread_mutex_unlock(&q->mutex);
  return x;
}

