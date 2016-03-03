#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

struct queue queue;

void *start_function() {
  pthread_t id = pthread_self();
  int popped;
  queue_pop(&queue, &popped);
  printf("thread: %d popped: %d\n",(int)id, popped);
  return NULL;
}
void *push_alot() {
  for (int i = 0; i < 3; i++) {
    queue_push(&queue, i);
  }
  return NULL;
}
int main() {
  pthread_t thread0;
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  queue_init(&queue);
  int ret = pthread_create(&thread0, NULL, &start_function, NULL);
  ret = pthread_create(&thread1, NULL, &push_alot , NULL);
  ret = pthread_create(&thread2, NULL, &start_function, NULL);
  ret = pthread_create(&thread3, NULL, &start_function, NULL);
  ret=ret;
  pthread_join(thread0, NULL);
  printf("yay! thread0 done\n");
  pthread_join(thread1, NULL);
  printf("yay! thread1 done\n");
  pthread_join(thread2, NULL);
  printf("yay! thread3 done\n");
  queue_destroy(&queue);
  printf("queue destroyed!!!");
  return 0;
}

