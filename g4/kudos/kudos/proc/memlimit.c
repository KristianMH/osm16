
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
  int pages = ((char*)new_end - (char*)old_end)/PAGE_SIZE +1;
  kprintf("pages: %d \n", pages);
  int diff = (char*)new_end - (char*)old_end;
  kprintf("diff: %d \n", diff);
  for (int i = 0; i < pages; i++) {
    phys_page = physmem_allocblock();
    memoryset((void*)ADDR_PHYS_TO_KERNEL(phys_page), 0, PAGE_SIZE);
    vm_map(table, phys_page, (virtaddr_t)old_end+PAGE_SIZE-diff, 1);    
  }

  process_get_current_process_entry()->heap_end = new_end;
  return new_end;  
}
