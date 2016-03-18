
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
  pagetable_t *table = thread_get_current_thread_entry()->pagetable;
  int diff = (int)new_end - (int)old_end;
  int pages = diff/PAGE_SIZE;
  int left_on_page = 4096 - (int)old_end % PAGE_SIZE;
 
  // attempt to reduce internal fragementaion.
  if (diff < left_on_page) {
    process_get_current_process_entry()->heap_end = new_end;
    return new_end;
  }
  for (int i = 0; i < pages; i++) {
    int vaddr = (int)old_end + PAGE_SIZE*(i+1);
    phys_page = physmem_allocblock();
    memoryset((void*)ADDR_PHYS_TO_KERNEL(phys_page), 0, PAGE_SIZE);
    vm_map(table, phys_page, vaddr, 1);    
  }

  process_get_current_process_entry()->heap_end = new_end;
  return new_end;  
}
