#ifndef STACK_H
#define STACK_H

struct stack_t {
  void **items;
  /* Invariant: n <= capacity */
  int n;
  int capacity;
};

void stack_init(struct stack_t *stack);

/* Zero on success */
int stack_push(struct stack_t *stack, void *x);

/* NULL on empty stack */
void* stack_pop(struct stack_t *stack);

int stack_empty(struct stack_t* stack);

void* stack_top(struct stack_t* stack);

void stack_destroy(struct stack_t *stack);

int stack_elements(struct stack_t* stack);
#endif
