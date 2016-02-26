#include "lib.h"

int main() {
  int spawn = syscall_spawn((const char*)&("[disk]hw.mips32"), NULL);
  printf("hw start\n");
  int join = syscall_join(spawn);
  printf("join return value : %d", join);
  syscall_halt();
  return 0;
}
