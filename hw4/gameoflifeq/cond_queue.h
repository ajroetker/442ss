#ifndef _COND_QUEUE
#define _COND_QUEUE

typedef struct _node {
    void * data;
    struct _node *next;
} node;

typedef struct _queue {
  node * head;
  node * tail;
  int size;
  unsigned* marked;

  pthread_mutex_t mutex;
  pthread_cond_t has_items;

} queue;

queue *queue_new(int univ_size);
int queue_is_empty(queue *q);
void enqueue(int x, queue *q);
int dequeue(queue *q);

#endif

