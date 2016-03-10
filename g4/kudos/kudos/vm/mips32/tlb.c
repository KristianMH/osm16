/*
 * TLB handling
 */

#include "kernel/panic.h"
#include "kernel/assert.h"
#include <tlb.h>
#include <pagetable.h>
#include "kernel/thread.h"
#include "proc/process.h"

// returns a index if found matching page entry. returns -1 if none found.
int find_matching_page(void) {
  tlb_exception_state_t state;
  _tlb_get_exception_state(&state);
  tlb_entry_t *entries = thread_get_current_thread_entry()->pagetable->entries;
  for (int i = 0; i < PAGETABLE_ENTRIES; i++) {
    if (entries[i].VPN2 == state.badvpn2) {
      return i;
    }
  }
  return -1;
}
void tlb_modified_exception(int mode) {
  // if 1 then it is a user thread.
  if (mode) {
    process_exit(-1);
  } else {
    KERNEL_PANIC("Kerne Panic fordi D bit is zero");
  }
}

void tlb_load_exception(int mode) {
  tlb_exception_state_t state;
  tlb_entry_t *entry;
  _tlb_get_exception_state(&state);
  // address on even? used for checking V0 and V1 for even and odd.
  int even = ADDR_IS_ON_EVEN_PAGE(state.badvaddr);
  int found_page = find_matching_page();
  if (found_page < 0) {
    if (mode) {
      process_exit(-1);
    } else {
      KERNEL_PANIC("TLB LOAD EXCEPTION: Page not found");
    }
  }
  entry = &thread_get_current_thread_entry()->pagetable->entries[found_page];
  if ((even && entry->V0) || (!even && entry->V1)) {
    _tlb_write_random(entry);
    return;
  }
  // if 1 then it is a user thread.
  if (mode) {
    process_exit(-1);
  } else {
    KERNEL_PANIC("TLB load exception: Invalid page");
  }
}

void tlb_store_exception(int mode) {
  tlb_exception_state_t state;
  tlb_entry_t *entry;
  _tlb_get_exception_state(&state);
  // address on even? used for checking V0 and V1 for even and odd.
  int even = ADDR_IS_ON_EVEN_PAGE(state.badvaddr);
  int found_page = find_matching_page();
  if (found_page < 0) {
    if (mode) {
      process_exit(-1);
    } else {
      KERNEL_PANIC("TLB STORE EXCEPTION: Page not found");
    }
  }
  entry = &thread_get_current_thread_entry()->pagetable->entries[found_page];
  // checks if dirty bit is set for even or odd pages.
  if ((even && entry->V0) || (!even && entry->V1)) {
    _tlb_write_random(entry);
    return;
  }
  // if 1 then it is a user thread.
  if (mode) {
    process_exit(-1);
  } else {
    KERNEL_PANIC("TLB STORE exception: Invalid page");
  }
}

/**
 * Fill TLB with given pagetable. This function is used to set memory
 * mappings in CP0's TLB before we have a proper TLB handling system.
 * This approach limits the maximum mapping size to 128kB.
 *
 * @param pagetable Mappings to write to TLB.
 *
 */

void tlb_fill(pagetable_t *pagetable)
{
  if(pagetable == NULL)
    return;

  /* Check that the pagetable can fit into TLB. This is needed until
     we have proper VM system, because the whole pagetable must fit
     into TLB. */
  KERNEL_ASSERT(pagetable->valid_count <= (_tlb_get_maxindex()+1));

  _tlb_write(pagetable->entries, 0, pagetable->valid_count);

  /* Set ASID field in Co-Processor 0 to match thread ID so that
     only entries with the ASID of the current thread will match in
     the TLB hardware. */
  _tlb_set_asid(pagetable->ASID);
}
