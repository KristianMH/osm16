#include "lib.h"

int main(void) {
  char str[12];
  int returnValue = syscall_read(0, &str, 12);
  //int returnValue = syscall_write(1, &str, 12);
  //returnValue = returnValue;
  syscall_halt();
  return returnValue;
}
