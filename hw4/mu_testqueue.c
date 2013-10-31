#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"
#include "mutex_queue.h"

typedef struct _threadinfo {
  int whoami;
  mutex_queue *queue;
} threadinfo;

typedef void *thread_main_t(void *);

void *addsub(threadinfo *ti) {
  int i;
  int x,y;

  int id = ti->whoami;
  mutex_queue *mq = ti->queue;

  for (i=0; i<1000; i++) {

    x = mq_dequeue(mq);
    y = mq_dequeue(mq);
    mq_enqueue(y,mq);
    mq_enqueue(x,mq);

  }
  printf("%d ",mq_dequeue(mq));
  printf("%d ",mq_dequeue(mq));
  return NULL;
}

int main(int argc, char **argv) {
  int i;

  pthread_t tid[4];
  threadinfo info[4];

  mutex_queue *q = mq_new(7);
  void *rv;

  for (i=0; i<4; i++) {
    info[i].whoami = i;
    info[i].queue = q;
    Pthread_create(&tid[i],NULL,(thread_main_t *)addsub,(void *)&info[i]);
  }

  for (i=1; i<=8; i++) {
    mq_enqueue(i,q);
  }

  for (i=0; i<4; i++) {
    Pthread_join(tid[i],&rv);
  }
  printf("\n");

  Pthread_exit(NULL);
} 
