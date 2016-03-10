#include "lib.h"

int main() {
  const char test[] = "test\0";
  usr_sem_t* dummy = syscall_usr_sem_open(test, 0);
  printf("Thread 1 is waiting for thread 2 to vacate\n");
  syscall_spawn("[disk]sem_w.mips32", NULL);
  syscall_usr_sem_procure(dummy);

  printf("Thread 1 is alive and going to destroy semaphore\n");
  syscall_usr_sem_destroy(dummy);
  syscall_halt();
  return 0;
}
