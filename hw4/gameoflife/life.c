#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

typedef struct _universe {
  int width;
  int height;
  unsigned * board;
} universe;

typedef struct _threadinfo {
  universe * universe1;
  universe * universe2;
  int * count;
  pthread_mutex_t * mutex;
  pthread_cond_t * cond;
  int start;
  int rows;
} threadinfo;

typedef void *thread_main_t(void *);

void show(universe * univ) {

  for (int y = 0; y < univ->height; y++) {
    for (int x = 0; x < univ->width; x++) {
      printf( univ->board[y * univ->width + x] ? "@" : " " );
    }
    printf("\n");
  }
  printf("\n");
}

void evolve(universe * univ, universe * next_gen,  int start, int end){
  for (int y = start; y < end; y++) {
    for (int x = 0; x < univ->width; x++) {
      int n = 0;
      for (int j = y - 1; j <= y + 1; j++) {
        for (int i = x - 1; i <= x + 1; i++) {
          if ( univ->board[(j % univ->height) * univ->width + (i % univ->width)] && !( j == y && i == x )) n++;
        }}
      next_gen->board[y*univ->width + x] = (n == 3 || (n == 2 && univ->board[y * univ->width + x])) ? 1 : 0;
    }}
  for (int y = start; y < end; y++) {
    for (int x = 0; x < univ->width; x++) {
      univ->board[y * univ->width + x] = next_gen->board[y*univ->width + x];
    }}
}

void *game_t(threadinfo * ti) {
  for (int i = 0; i < 50; i++){
    if (i % 2) {
    evolve(ti->universe2, ti->universe1, ti->start, ti->start + ti->rows);
    } else {
    evolve(ti->universe1, ti->universe2, ti->start, ti->start + ti->rows);
    }
    pthread_mutex_lock(ti->mutex);
    *(ti->count) = *(ti->count) + 1;
    if (*(ti->count) < 4) pthread_cond_wait(ti->cond,ti->mutex);
    if (*(ti->count) == 4) {
      *(ti->count) = *(ti->count) - 1;
      for (NULL; *(ti->count) > 0; *(ti->count) = *(ti->count) - 1) pthread_cond_signal(ti->cond);}
    pthread_mutex_unlock(ti->mutex);
  }
  return NULL;
}

int main (int argc, char **argv){
  int i;
  int w = 0, h = 0;
  int ts = 4;

  pthread_t tid[ts];
  threadinfo info[ts];

  int count = 0;
  pthread_mutex_t mutex;
  pthread_cond_t all_done;

  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&all_done,NULL);

  void *rv;




  if (argc > 1) w = atoi(argv[1]);
  if (argc > 2) h = atoi(argv[2]);
  if (w <= 0) w = 250;
  if (h <= 0) h = 250;

  universe * univ = (universe *)malloc(sizeof(universe));
  univ->board = (unsigned *)malloc(sizeof(unsigned) * w * h);
  univ->width = w;
  univ->height = h;
  universe * univ2 = (universe *)malloc(sizeof(universe));
  univ2->board = (unsigned *)malloc(sizeof(unsigned) * w * h);
  univ2->width = w;
  univ2->height = h;

  for (int y = 0; y < univ->height; y++) {
    for (int x = 0; x < univ->width; x++) {
      univ->board[y * univ->width + x] = rand() % 2;
    }}

  show(univ);
  for (i=0; i<ts; i++) {
    info[i].universe1 = univ;
    info[i].universe2 = univ2;
    info[i].count = &count;
    info[i].mutex = &mutex;
    info[i].cond = &all_done;
    info[i].start = i*h/ts;
    info[i].rows = h/ts;
    if (i == ts - 1) info[i].rows = h/ts + h%ts;
    Pthread_create(&tid[i],NULL,(thread_main_t *)game_t,(void *)&info[i]);
  }




  for (i=0; i<ts; i++) {
    Pthread_join(tid[i],&rv);
  }

  show(univ);
  printf("\n");

  Pthread_exit(NULL);
}
