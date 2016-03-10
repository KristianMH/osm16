
#include "vm/memory.h"
#include "lib/types.h"
#include "lib/libc.h"
#include "proc/process.h"

void *memlimit(void* new_end) {
  uintptr_t phys_page;
  void *old_end = process_get_current_process_entry()->heap_end;
  if (new_end == NULL) {
    return old_end;
  }
  if (new_end < old_end) {
    return NULL;
  }
  phys_page = physmem_allocblock()
  return old_end;  
}
