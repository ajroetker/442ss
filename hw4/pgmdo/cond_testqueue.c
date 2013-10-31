#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"
#include "cond_queue.h"

typedef struct _threadinfo {
  int whoami;
  queue *queue;
} threadinfo;

typedef void *thread_main_t(void *);

void *addsub(threadinfo *ti) {
  int i;
  int x,y;

  int id = ti->whoami;
  queue *q = ti->queue;

  for (i=0; i<1000; i++) {

    x = dequeue(q);
    y = dequeue(q);
    enqueue(y,q);
    enqueue(x,q);

  }
  printf("%d ",dequeue(q));
  printf("%d ",dequeue(q));
  return NULL;
}

int main(int argc, char **argv) {
  int i;

  pthread_t tid[4];
  threadinfo info[4];

  queue *q = queue_new(7);
  void *rv;

  for (i=0; i<4; i++) {
    info[i].whoami = i;
    info[i].queue = q;
    Pthread_create(&tid[i],NULL,(thread_main_t *)addsub,(void *)&info[i]);
  }

  for (i=1; i<=8; i++) {
    enqueue(i,q);
  }

  for (i=0; i<4; i++) {
    Pthread_join(tid[i],&rv);
  }
  printf("\n");

  Pthread_exit(NULL);
}
