#include "lib.h"

int main() {
  char* heap_end;
  heap_end = syscall_memlimit(NULL);

  #define test_string "Extra mem here\n"
  #define test_string_1 "even more mem\n"
  #define test_string_length 15
  #define test_string_length_1 14
  
  if (syscall_memlimit(heap_end + test_string_length) == NULL) {
    printf("ERROR from memlimit");
    return 1;
  }

  for (int i = 0; i < test_string_length; i++) {
    heap_end[i] = test_string[i];
  }

  /*Locating updated heap end
  heap_end = syscall_memlimit(NULL);

  if (syscall_memlimit(heap_end + test_string_length_1) == NULL) {
    printf("ERROR from memlimit");
    return 1;
  }

  for (int i = 0; i < test_string_length_1; i++) {
    heap_end[i] = test_string_1[i];
    }*/

  syscall_write(1, heap_end, test_string_length);
  return 0;
  
}
