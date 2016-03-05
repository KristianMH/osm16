#include "lib.h"

int main() {
  printf("Yay we started first program\n");
  int spawn = syscall_spawn("[disk]phello.mips32", NULL);
  //printf("now we're waiting for hello");
  int join = syscall_join(spawn);
  printf("join return value : %d\n", join);
  syscall_halt();
  return 0;
}
