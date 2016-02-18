#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void exchange(struct queue *queue, int i, int j) {
 int temp = queue->root[j];
 queue->root[j] = queue->root[i];
 queue->root[i] = temp;
}

int queue_init(struct queue *queue) {
  queue->root = NULL;
  queue->size = 0;
  queue->capacity = 0;
  return 0;
}
int queue_destroy(struct queue *queue) {
  free(queue->root);
  return 0;
}
int queue_size(struct queue *queue) {
  return queue->size;
}
int queue_push(struct queue *queue, int pri) {
  int newNode = pri;
  if (queue->size == queue->capacity) {
    queue->capacity = (queue->capacity+1)*2;
    queue->root = realloc(queue->root, sizeof(newNode)*queue->capacity);
  }

  //index of new node
  int index = queue->size;
  queue->size++;
  queue->root[index] = newNode;
  if (index == 0) {
    queue->root[0] = newNode;
  }
  while (queue->root[PARENT(index)] < queue->root[index]) {
    exchange(queue, index, PARENT(index));
    index = PARENT(index);
  }
  return 0;
 
}

void max_heapify(struct queue *queue, int index){
  int left = RIGHT(index);
  int right = LEFT(index);
  int left_priority = queue->root[left];
  int right_priority = queue->root[right];
  int index_priority = queue->root[index];
  int largest;
  if (left < queue->size && left_priority > right_priority) {
    largest = left;
  } else {
    largest = index;
  }
  if (right < queue->size && right_priority > queue->root[largest]) {
    largest=right;
  }
  if (index_priority !=  queue->root[largest]) {
    exchange(queue, index, largest);
    max_heapify(queue, largest);
  }
}
//pops the root since it has higest priority
int queue_pop(struct queue *queue, int *pri_ptr) {
  if (queue->size < 1) {
    return 1;
  }
  int prio = *queue->root;
  *pri_ptr = prio;
  queue->size--;
  exchange(queue, 0, queue->size);
  max_heapify(queue, 0);
  return 0;
}

