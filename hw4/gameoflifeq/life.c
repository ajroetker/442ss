#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"
#include "cond_queue.h"

typedef struct _universe {
  int width;
  int height;
  unsigned * board;
} universe;

typedef struct _threadinfo {
  universe * universe1;
  universe * universe2;
  pthread_mutex_t * mutex;
  pthread_cond_t * cond;
  int * gen;
  int * count;
  queue * q1;
  queue * q2;
} threadinfo;

typedef void *thread_main_t(void *);

void show(universe * univ) {
  int w = univ->width;
  int h = univ->height;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      printf( univ->board[y * w + x] ? "@" : " " );
    }
    printf("\n");
  }
  printf("\n");
}

void evolve(universe * univ, universe * next_gen, int x, int y, queue * q){
  int w = univ->width, h = univ->height;
  int n = 0;
  for (int j = y - 1; j <= y + 1; j++) {
    for (int i = x - 1; i <= x + 1; i++) {
      if ( univ->board[((j+h) % h) * w + (i+w % w)] && !( j == y && i == x )) n++;
    }}
  next_gen->board[y*w + x] = (n == 3 || (n == 2 && univ->board[y * w + x])) ? 1 : 0;
  if (next_gen->board[y*w + x] != univ->board[y*w + x])
    for (int j = y - 1; j <= y + 1; j++) {
      for (int i = x - 1; i <= x + 1; i++) {
        enqueue(((j+h) % h) * w + ((i+w) % w), q);
      }}
}

void *game_t(threadinfo * ti) {
  int x, y, c, *count;
  threadinfo t = *ti;
  while(*(t.gen) < 201){
    if (*(t.gen) % 2 == 0) {
      pthread_mutex_lock(t.mutex);
      if (queue_is_empty(t.q1)) {
        count = t.count;
        *count = *count + 1;
        if (*count < 4) pthread_cond_wait(t.cond,t.mutex);
        if (*count == 4) {
          *count = *count - 1;
          *(t.gen) = *(t.gen) + 1;
          for (NULL; *count > 0; *count = *count - 1) pthread_cond_signal(t.cond);
        }
        pthread_mutex_unlock(t.mutex);
      } else {
        c = dequeue(t.q1);
        pthread_mutex_unlock(t.mutex);
        y = c/t.universe1->width;
        x = c%t.universe1->width;
        evolve(t.universe1, t.universe2, x, y, t.q2);
      }
    }
    else {
      pthread_mutex_lock(t.mutex);
      if (queue_is_empty(t.q2)) {
        *count = *count + 1;
        if (*count < 4) pthread_cond_wait(t.cond,t.mutex);
        if (*count == 4) {
          *count = *count - 1;
          for (NULL; *count > 0; *count = *count - 1) pthread_cond_signal(t.cond);
          *(t.gen) = *(t.gen) + 1;
        }
        pthread_mutex_unlock(t.mutex);
      } else {
        c = dequeue(t.q2);
        pthread_mutex_unlock(t.mutex);
        y = c/t.universe1->width;
        x = c%t.universe1->width;
        evolve(t.universe1, t.universe2, x, y, t.q1);
      }
    }
  }
  return NULL;
}

int main (int argc, char **argv){
  int i;
  int w = 0, h = 0;
  int ts = 4;

  pthread_t tid[ts];
  threadinfo info[ts];

  int gen = 0;
  int count = 0;
  pthread_mutex_t mutex;
  pthread_cond_t cond;

  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);

  void *rv;

  if (argc > 1) w = atoi(argv[1]);
  if (argc > 2) h = atoi(argv[2]);
  if (w <= 0) w = 250;
  if (h <= 0) h = 250;

  universe univs[2];

  universe * univ = &univs[0];
  univ->board = (unsigned *)malloc(sizeof(unsigned) * w * h);
  univ->width = w;
  univ->height = h;
  universe * univ2 = &univs[1];
  univ2->board = (unsigned *)malloc(sizeof(unsigned) * w * h);
  univ2->width = w;
  univ2->height = h;

  queue * q = queue_new(w*h);
  queue * q2 = queue_new(w*h);
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      univ->board[y * w + x] = rand() % 2;
      enqueue((y*w + x), q);
    }}

  show(univ);
  for (i=0; i<ts; i++) {
    info[i].universe1 = univ;
    info[i].universe2 = univ2;
    info[i].gen = &gen;
    info[i].count = &count;
    info[i].mutex = &mutex;
    info[i].cond = &cond;
    info[i].q1 = q;
    info[i].q2 = q2;
    Pthread_create(&tid[i],NULL,(thread_main_t *)game_t,(void *)&info[i]);
  }

  for (i=0; i<ts; i++) {
    Pthread_join(tid[i],&rv);
  }

  show(univ);
  printf("\n");

  Pthread_exit(NULL);
}
