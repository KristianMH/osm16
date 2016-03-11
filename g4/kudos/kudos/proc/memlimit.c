
#include "vm/memory.h"
#include "lib/types.h"
#include "lib/libc.h"
#include "proc/process.h"
#include "kernel/thread.h"
#include "proc/elf.h"
void *memlimit(void* new_end) {
  uintptr_t phys_page;
  void *old_end = process_get_current_process_entry()->heap_end;
  if (new_end == NULL) {
    return old_end;
  }
  if (new_end < old_end) {
    return NULL;
  }
  phys_page = physmem_allocblock();
  memoryset((void*)ADDR_PHYS_TO_KERNEL(phys_page), 0, PAGE_SIZE);
  vm_map(thread_get_current_thread_entry()->pagetable, phys_page, (virtaddr_t)old_end, 1);
  process_get_current_process_entry()->heap_end = new_end;
  return new_end;  
}
