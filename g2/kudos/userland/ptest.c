#include "lib.h"

int main() {
  printf("Yay we started first program\n");
  int spawn = syscall_spawn("[disk]phello.mips32", NULL);
  printf()
  int join = syscall_join(spawn);
  printf("join return value : %d", join);
  syscall_halt();
  return 0;
}
