
#include "vm/memory.h"
#include "lib/types.h"
#include "lib/libc.h"


void *memlimit(void* new_end) {
  if (new_end == NULL) {
    return NULL;
  }
  kprintf("hej\n");
  return NULL;
  
}
