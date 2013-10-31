#ifndef _COND_QUEUE
#define _COND_QUEUE

typedef int T;

typedef struct _queue {

  int capacity;
  T *elements;

  int head;
  int tail;

  int items;
  int slots;

  pthread_mutex_t mutex;
  pthread_cond_t has_items;
  pthread_cond_t has_slots;


} queue;

queue *queue_new(int c);
int queue_is_empty(queue *q);
int queue_is_full(queue *q);
void enqueue(T x, queue *q);
T dequeue(queue *q);

#endif

