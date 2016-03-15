#include "lib.h"

int main() {
  char buffer[64];
  int ret = syscall_open("[disk]rw.c");
  printf("open : %d \n", ret);
  ret = syscall_open("[disk]lib.c");
  printf("open : %d \n", ret);
  ret = syscall_read(ret, (char*)&buffer, 64);
  printf((const char *)&buffer);
  printf("\n");
  ret = syscall_open("[disk]test.c");
  printf("open : %d \n", ret);
  ret = syscall_read(ret, (char*)&buffer, 64);
  printf((const char *)&buffer);
  printf("\n");
  ret = syscall_open("[disk]tes.c");
  printf("open negative: %d \n", ret);
  ret = syscall_close(3);
  printf("close: %d\n", ret);
  ret = syscall_close(4);
  printf("close: %d\n", ret);
  ret = syscall_close(5);
  printf("close: %d\n", ret);
  ret = syscall_create("[disk]simon.py", 16);
  printf("create : %d\n", ret);
  ret = syscall_open("[disk]simon.py");
  printf("open : %d \n", ret);
  ret = syscall_seek(ret, 10);
  printf("seek : %d \n", ret);
  ret = syscall_filecount("[disk]");
  printf("count: %d \n", ret);
  ret = syscall_delete("[disk]simon.py");
  printf("delete : %d\n", ret);
  ret = syscall_delete("[disk]mikkel.html");
  printf("delete negative : %d\n", ret);
  ret = syscall_filecount("[disk]");
  printf("count: %d \n", ret);
  ret = syscall_file("[disk]", 0, (char*)&buffer);
  printf("file : %d \n", ret);
  
  /* ret = syscall_create("[disk]simon.c", 16); */
  /* printf("create : %d\n", ret); */
  /* ret = syscall_open("[disk]simon.c"); */
  /* printf("open : %d\n", ret); */
  /* int written = syscall_write(ret, "hej med dig\n", 15); */
  /* printf("written : %d\n", written); */
  /* char buffer1[30]; */
  /* ret = syscall_read(ret, (char*)&buffer1, 1); */
  /* printf("read : %d\n", ret); */
  /* printf((const char *) &buffer1); */
  /* ret = syscall_delete("[disk]simon.c"); */
  /* printf("delete : %d\n", ret); */

  
  syscall_halt();
  return 0;
}
