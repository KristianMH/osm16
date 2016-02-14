#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


static void out_of_memory() {
  printf("Out of memory.\n");
  exit(EXIT_FAILURE);
}
void plus(struct stack_t *stack){
  if (stack_elements(stack) < 2) {
    printf("missing numbers on the stack\n");
    return;
  }
  double *x = stack_pop(stack);
  double *y = stack_pop(stack);
  double* d;
  if ((d = (double*)malloc(sizeof(double))) == NULL) {
    out_of_memory();
  }
  *d = *x+*y;
  if (stack_push(stack,d) != 0) {
    out_of_memory();
  }
  printf("%lf\n",*d);
  return;
}

int main() {
  double x;
  int c;
  struct stack_t stack;
  stack_init(&stack);
  while (1) {
    c=getc(stdin);
    switch (c) {
    case EOF:
      exit(EXIT_SUCCESS);
    case '+':
      plus(&stack);
      break;
    case '-':
      break;
    case '*':
      break;
    case '/':
      break;
    case 'p':
      if (stack_empty(&stack)) {
        printf("Stack is empty.\n");
      } else {
        printf("%lf\n", *(double*)stack_pop(&stack));
      }
      break;
    default:
      ungetc(c,stdin);
      if (scanf("%lf",&x) == 1) {
        double* d;
        if ((d = (double*)malloc(sizeof(double))) == NULL) {
          out_of_memory();
        } else {
          *d = x;
          if (stack_push(&stack,d) != 0) {
            out_of_memory();
          }
        }
      } else {
        printf("Bad input.\n");
      }
    }
    while (getc(stdin)!='\n');
  }
}
