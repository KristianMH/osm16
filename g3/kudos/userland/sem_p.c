#include "lib.h"

int main() {
  const char test[20] = "Testing semaphore";
  usr_sem_t* dummy = syscall_usr_sem_open(test, 1);
  printf("Now i am going to hold and i won't return");
  syscall_usr_sem_procure(dummy);
  syscall_usr_sem_procure(dummy);
  return 0;
}
