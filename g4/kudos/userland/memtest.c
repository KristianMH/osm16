#include "lib.h"

#define empty_string_length 0
#define neg_string_length -26
  
#define test_string "Extra mem here\n"
#define test_string_1 "even more mem\n"
#define test_string_length 15
#define test_string_length_1 14

int main() {
  char* heap_end;
  heap_end = syscall_memlimit(NULL);  

//Testing that heap end doesn't change, when allocating for epmty string
  if (syscall_memlimit(heap_end + empty_string_length) != heap_end) {
    printf("Allocated memory for empty string\n");
    return 1;
  }
  
// Testing that NULL is returned in case of new_heap_end < old_heap_end
  if (syscall_memlimit(heap_end + neg_string_length) != NULL) {
    printf("New heap end lower than old heap_end\n");
    return 1;
  }
    
  if (syscall_memlimit(heap_end + test_string_length) == NULL) {
    printf("ERROR from memlimit");
    return 1;
  }

  for (int i = 0; i < test_string_length; i++) {
    heap_end[i] = test_string[i];
  }
  syscall_write(1, heap_end, test_string_length);
  /* Locating updated heap end */
  heap_end = syscall_memlimit(NULL);

  if (syscall_memlimit(heap_end + test_string_length_1+3807) == NULL) {
    printf("ERROR from memlimit");
    return 1;
  }

  for (int i = 0; i < test_string_length_1; i++) {
    heap_end[i] = test_string_1[i];
    }

  syscall_write(1, heap_end, test_string_length_1);
  printf("\nTest went well\n");
  return 0;
  
}
