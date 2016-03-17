#include "lib.h"

int main() {
  char buffer[64];

  int ret = syscall_open("[disk]rw.c");
  if (ret != 3) {
    printf("open rw.c failed\n expected 3 got: %d \n",ret);
    syscall_halt();
  }
  ret = syscall_open("[disk]lib.c");
  if (ret != 4) {
    printf("open lib.c failed\n expected 4 got: %d \n",ret);
    syscall_halt();
  }
  ret = syscall_read(ret, (char*)&buffer, 64);
  if (ret <= 0) {
    printf("couldn't read from lib.c file\n");
    syscall_halt();
  }
  ret = syscall_open("[disk]test.c");
  if (ret != 5) {
    printf("open rw.c failed\n expected 5 got: %d \n",ret);
    syscall_halt();
  }
  ret = syscall_read(ret, (char*)&buffer, 64);
  if (ret <= 0) {
    printf("couldn't read from test.c file\n");
    syscall_halt();
  }
  ret = syscall_open("[disk]tes.c");
  if (ret > 0) {
    printf("SYSCALL_OPEN could open a non-existing file ?? \n");
    syscall_halt();
  }
  ret = syscall_close(3);
  if (ret != 0) {
    printf("ret : %d", ret);
    printf("Could not close filehandle 3\n");
    syscall_halt();
  }
  ret = syscall_close(4);
  if (ret != 0) {
    printf("Could not close filehandle 4\n");
    syscall_halt();
  }
  ret = syscall_close(5);
  if (ret != 0) {
    printf("Could not close filehandle 5\n");
    syscall_halt();
  }
  ret = syscall_create("[disk]simon.py", 16);
  if (ret != 0) {
    printf("Couldn't create simon.py file ??\n");
    syscall_halt();
  }
  ret = syscall_open("[disk]simon.py");
  if (ret != 3) {
    printf("open rw.c failed\n expected 3 got: %d \n",ret);
  }
  ret = syscall_seek(ret, 10);
  if (ret != 0) {
    printf("couldn't seek simon.py file \n");
    syscall_halt();
  }
  ret = syscall_close(3);
  if (ret != 0) {
    printf("Could not close filehandle 3\n");
    syscall_halt();
  }
  ret = syscall_delete("[disk]simon.py");
  if (ret != 0) {
    printf("couldn't delete simon.py file \n");
    syscall_halt();
  }
  ret = syscall_delete("[disk]mikkel.html");
  if (ret == 0) {
    printf("Somehow we deleted a non-existing file \n");
    syscall_halt();
  }
  /* ret = syscall_filecount("[disk]"); */
  /* //tba */
  /* ret = syscall_file("[disk]", 0, (char*)&buffer); */
  /* //tba */

  printf("Testing went fine, shutting down\n");
  syscall_halt();
  return 0;
}
