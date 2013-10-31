#ifndef _MUTEX_QUEUE
#define _MUTEX_QUEUE

typedef int T;

typedef struct _mutex_queue {

  int capacity;
  T *elements;

  int head;
  int tail;

  int items;
  int slots;

  pthread_mutex_t mutex;

} mutex_queue;

mutex_queue *mq_new(int c);
int mq_is_empty(mutex_queue *mq);
int mq_is_full(mutex_queue *mq);
void mq_enqueue(T x, mutex_queue *mq);
T mq_dequeue(mutex_queue *mq);

#endif

