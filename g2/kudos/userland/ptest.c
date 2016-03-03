#include "lib.h"

int main() {
  /*printf("hej");
  int spawn = syscall_spawn((char const*)&("[disk]phello.mips32"), NULL);
  printf("halt start\n");
  int join = syscall_join(spawn);
  printf("join return value : %d", join);*/
  syscall_halt();
  return 0;
}
