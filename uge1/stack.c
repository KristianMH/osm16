#include <stdlib.h>

#include "stack.h"

void stack_init(struct stack_t *stack) {
  stack->items = NULL;
  stack->n = 0;
  stack->capacity = 0;
}

int stack_push(struct stack_t *stack, void *x) {
  if (stack->n == stack->capacity) {
    stack->capacity = (stack->capacity + 1) * 2;
    void **new_items =
      realloc(stack->items,
              sizeof(void*) * stack->capacity);

    if (new_items == NULL) {
      return 1;
    }

    stack->items = new_items;
  }

  stack->items[stack->n] = x;
  stack->n++;

  return 0;
}

void* stack_pop(struct stack_t *stack) {
  if (stack->n == 0) {
    return NULL;
  }

  return stack->items[--stack->n];
}

int stack_empty(struct stack_t* stack) {
  return stack->n == 0;
}

void* stack_top(struct stack_t* stack) {
  if (stack->n == 0) {
    return NULL;
  }

  return stack->items[stack->n-1];
}
int stack_elements(struct stack_t* stack){
  return stack->n;
}
void stack_destroy(struct stack_t *stack) {
  free(stack->items);
}
