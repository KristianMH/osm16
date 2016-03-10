#include "lib.h"

int main() {
  const char test[] = "test\0";
  usr_sem_t* dummy = syscall_usr_sem_open(test, -1);
  printf("thread 2 spawned and vacating the semaphore\n");
  syscall_usr_sem_vacate(dummy);
  return 0;
}
