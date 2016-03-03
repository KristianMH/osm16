#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

struct queue queue;

void *start_function() {
  pthread_t id = pthread_self();
  //printf("thread nr: %d started.\n", (int)id);
  int ret;
  int popped;
  ret = queue_pop(&queue, &popped);
  ret = ret;
  printf("thread: %d popped: %d\n",(int)id, popped);
  pthread_exit(NULL);
  return NULL;
}
void *push_alot() {
  printf("pushing started\n");
  for (int i = 0; i < 10000; i++) {
    int ret = queue_push(&queue, i);
    ret=ret;
  }
  printf("pushing stopped\n");
  pthread_exit(NULL);
  return NULL;
}
int main() {
  pthread_t thread0;
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  queue_init(&queue);
  int ret = pthread_create(&thread0, NULL, &push_alot, NULL);
  printf("ret: %d\n", ret);
  ret = pthread_create(&thread1, NULL, &start_function , NULL);
  ret = pthread_create(&thread2, NULL, &start_function, NULL);
  ret = pthread_create(&thread3, NULL, &start_function, NULL);
  return 0;
}

