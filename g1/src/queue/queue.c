#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
// swaps the position of two nodes in the heap
void exchange(struct queue *queue, int i, int j) {
 int temp = queue->root[j];
 queue->root[j] = queue->root[i];
 queue->root[i] = temp;
}

// initalizeses the queue.
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

int queue_push(struct queue *queue, int pri) {
  int newNode = pri;
  //if queue reached max capacity more space will be allocated
  if (queue->size == queue->capacity) {
    queue->capacity = (queue->capacity+1)*2;
    int *newRoot = realloc(queue->root, sizeof(newNode)*queue->capacity);
    // checks if realloc failed.
    if (newRoot == NULL) {
      return 1;
    }
    queue->root = newRoot;
  }

  //index of new node
  int index = queue->size;
  queue->size++;
  // inserts new node last in queue.
  queue->root[index] = newNode;
  // checks bottom-up the new node and its parents
  while (queue->root[PARENT(index)] < queue->root[index]) {
    exchange(queue, index, PARENT(index));
    index = PARENT(index);
  }
  return 0;
 
}
// restories max heap attribute from a given index to the last element.
void max_heapify(struct queue *queue, int index){
  int left = RIGHT(index);
  int right = LEFT(index);
  int index_priority = queue->root[index];
  int largest;
  if (left < queue->size && queue->root[left] > index_priority) {
    largest = left;
  } else {
    largest = index;
  }
  if (right < queue->size && queue->root[right] > queue->root[largest]) {
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
  *pri_ptr = *queue->root;
  queue->size--;
  //sets the last item in the heap is new root and recursivly max_heapify
  exchange(queue, 0, queue->size);
  max_heapify(queue, 0);
  return 0;
}

