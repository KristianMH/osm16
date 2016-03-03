#include "lib.h"

int main() {
  const char trold[20] = "Mikkel Trolle";
  usr_sem_t* dummy = syscall_usr_sem_open(trold, 1);
  int ret = syscall_usr_sem_procure(dummy);
  ret = syscall_usr_sem_procure(dummy);
  printf("procure: %d\n", ret);
  ret = syscall_usr_sem_vacate(dummy);
  printf("vacate: %d\n", ret);
  ret = syscall_usr_sem_destroy(dummy);
  printf("destroy: %d\n", ret);
  syscall_halt();
  return 0;
}
