#include "lib.h"

int main() {
  char foo[100];
  foo[99] = 'a';
  if (*foo) {
    
  }
  printf("hej no tlb exception?\n");
  syscall_halt();
  return 0;
}
