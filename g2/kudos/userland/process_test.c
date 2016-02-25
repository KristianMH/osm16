

#include "lib.h"

int main(void) {
  syscall_halt();
  return 0;
}

/*intt main() {
    int spawn = syscall_spawn((const char*)&("[disk]oldshell.mips32"), NULL);
  printf("oldshell start\n");
  int join = syscall_join(spawn);
  join=join;
  //printf("join return value : %d", join);
  syscall_halt();
  return 0;
}
*/
