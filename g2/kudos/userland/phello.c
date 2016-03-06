#include "lib.h"

int main() {
  printf("hello from phello\n");
  syscall_exit(42);
  return 0;
}
