#include "lib.h"

int main() {
  syscall_spawn("[disk]hw.mips32", NULL);
  return 0;
}
