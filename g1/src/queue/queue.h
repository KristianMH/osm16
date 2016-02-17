#ifndef QUEUE_H
#define QUEUE_H
// marcos for navigating in heap
#define PARENT(i) (i)/2 
#define RIGHT(i) i*2
#define LEFT(i) i*2+1

struct node {
  //void* thing; //perhaps a program address that could be stored here?
  int priority;
};

//heap based queue structure. Root has highest priority.
struct queue{
  struct node* root;
  int size;
  int capacity; //allocated space
};

int queue_init(struct queue *queue);
int queue_destroy(struct queue *queue);
int queue_size(struct queue *queue);
int queue_push(struct queue *queue, int pri);
int queue_pop(struct queue *queue, int *pri_ptr);

#endif
