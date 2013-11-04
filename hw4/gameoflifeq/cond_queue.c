#include <pthread.h>
#include <stdlib.h>
#include "csapp.h"
#include "cond_queue.h"

queue *queue_new(int universe_size) {
  queue *q = (queue *)malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  q->marked = (unsigned *)malloc(sizeof(unsigned)*universe_size);
  for (int i = 0; i < universe_size; i++) q->marked[i] = 0;
  pthread_mutex_init(&q->mutex,NULL);
  pthread_cond_init(&q->has_items,NULL);
  return q;
}

int queue_is_empty(queue *q) {
  int is_empty;
  is_empty = (q->size == 0);
  return is_empty;
}

void enqueue(int x, queue *q) {
  pthread_mutex_lock(&q->mutex);
  if (!q->marked[x]) {
    q->marked[x] = 1;
    node * n = (node *)malloc(sizeof(node));
    n->data = x;
    if (q->size == 0) {
      q->head = n;
    } else {
      q->tail->next = n;
    }
    q->tail = n;
    q->size++;
    pthread_cond_signal(&q->has_items);
  }
  pthread_mutex_unlock(&q->mutex);
}

int dequeue(queue *q) {
  int x;
  pthread_mutex_lock(&q->mutex);
  // wait until item is available
  while (q->size == 0) {
    pthread_cond_wait(&q->has_items,&q->mutex);
  }
  x = q->head->data;
  node * n = q->head->next;
  free(q->head);
  q->head = n;
  q->size--;
  q->marked[x] = 0;
  pthread_mutex_unlock(&q->mutex);
  return x;
}

