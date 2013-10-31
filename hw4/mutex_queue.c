#include <pthread.h>
#include <stdlib.h>
#include "csapp.h"
#include "mutex_queue.h"

mutex_queue *mq_new(int c) {
  mutex_queue *mq = (mutex_queue *)malloc(sizeof(mutex_queue));
  mq->capacity = c;
  mq->elements = (T *)malloc(c*sizeof(T));
  mq->head = 0;
  mq->tail = 0;
  mq->items = 0;
  mq->slots = c;
  pthread_mutex_init(&mq->mutex,NULL);
  return mq;
}



int mq_is_empty(mutex_queue *mq) {
  int is_empty;
  pthread_mutex_lock(&mq->mutex);
  is_empty = (mq->items == 0);
  pthread_mutex_unlock(&mq->mutex);
  return is_empty;
}

int mq_is_full(mutex_queue *mq) {
  int is_full;
  pthread_mutex_lock(&mq->mutex);
  is_full = (mq->slots == 0);
  pthread_mutex_unlock(&mq->mutex);
  return is_full;
}

void mq_enqueue(T x, mutex_queue *mq) {
  pthread_mutex_lock(&mq->mutex);
  // wait until slot is available
  while (mq->slots == 0) {
    pthread_mutex_unlock(&mq->mutex);
    pthread_yield();
    pthread_mutex_lock(&mq->mutex);
  }
  mq->elements[mq->tail] = x;
  mq->tail = (mq->tail + 1) % mq->capacity;
  mq->items++;
  mq->slots--;
  pthread_mutex_unlock(&mq->mutex);
}








T mq_dequeue(mutex_queue *mq) {
  int x;
  pthread_mutex_lock(&mq->mutex);
  // wait until item is available
  while (mq->items == 0) {
    pthread_mutex_unlock(&mq->mutex);
    pthread_yield();
    pthread_mutex_lock(&mq->mutex);
  }
  x = mq->elements[mq->head];
  mq->head = (mq->head + 1) % mq->capacity;
  mq->items--;
  mq->slots++;
  pthread_mutex_unlock(&mq->mutex);
  return x;
}

