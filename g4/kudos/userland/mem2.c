#include "lib.h"

#define A 14

#define S "Nice string 1\n"
#define R "Nice string 2\n"
#define T "Nice string 3\n"

int main() {
  char* a_string;
  char* b_string;
  char* c_string;

  size_t i;

  a_string = syscall_memlimit(NULL);

  if (syscall_memlimit(a_string + A) == NULL) {
    return 1;
  }
  for (i = 0; i < A; i++) {
    a_string[i] = S[i];
  }

  b_string = syscall_memlimit(NULL);

  if (syscall_memlimit(b_string + A) == NULL) {
    return 1;
  }
  for (i = 0; i < A; i++) {
    b_string[i] = R[i];
  }

  c_string = syscall_memlimit(NULL);

  if (syscall_memlimit(c_string + A) == NULL) {
    return 1;
  }
  for (i = 0; i < A; i++) {
    c_string[i] = T[i];
  }

  /* Write from the dynamically allocated memory. */
  syscall_write(1, a_string, A);
  syscall_write(1, b_string, A);
  syscall_write(1, c_string, A);


  return 0;
}
