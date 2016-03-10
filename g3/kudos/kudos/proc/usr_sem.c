/*
 * Userland semaphore implementation.
 */

#include "usr_sem.h"
#include "lib/libc.h"

static spinlock_t usr_sem_table_slock;
// userland semaphore array
usr_sem_t sem_array[USR_SEM_MAX_SEMAPHORES];

// finds a free entry in array, negative value on no space
int find_sem_space() {
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    if (sem_array[i].init == -1) {
      return i;
    }
  }
  return -1;
}

void usr_sem_init() {
  spinlock_reset(&usr_sem_table_slock);
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    sem_array[i].init = -1;
  }
}

// returns an existing semaphore with same name.
int compare_sem_name(const char* name) {
  kprintf(name);
  kprintf("\n");
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    if (sem_array[i].init == 0 &&
        stringcmp((const char*)&sem_array[i].name, name) == 0) {
      kprintf("found a name");
      return i;
    }
  }
  return -1;
}

// Returns a pointer to a userland semaphore
usr_sem_t* usr_sem_open(const char* name, int value) {
  interrupt_status_t intr_status;
  intr_status = _interrupt_disable();
  spinlock_acquire(&usr_sem_table_slock);
  //char* name1;
  int space = find_sem_space();
  int same_name = compare_sem_name(name);
  usr_sem_t* dummy = &sem_array[space];
  kprintf("same_name: %d \n", same_name);
  if (value < 0) {
    kprintf("hay\n");
    if (same_name == -1) {
      return NULL;
    }
    return &sem_array[same_name];
  }
  if (value >= 0) {
    if (same_name >= 0) {
      return NULL;
    }    
  }
  if (space < 0) {
    kprintf("no space for sem");
    return 0;
  }
  /*
  for (int i = 0; i < 20; i++) {
    name1[i] = name[i];
    if (name[i] == '\0') {
      break;
    }
  }*/
  *dummy->name = name;
  dummy->kern_sem = semaphore_create(value);
  dummy->init = 0;
  spinlock_release(&usr_sem_table_slock);
  _interrupt_set_state(intr_status);
  return dummy;
}

// destroys a userland semaphore, returns negative number on error
int usr_sem_destroy(usr_sem_t* sem) {
  if (sem->kern_sem->value < 0) {
    //threads blocking the semaphore
    return -1;
  }
  sem->init = -1;
  semaphore_destroy(sem->kern_sem);
  return 0;
}

// vacate the userland semaphore, returns negative number on error
int usr_sem_vacate(usr_sem_t* sem) {
  semaphore_V(sem->kern_sem);
  return 0;
}

// procure the userland semaphore, returns negative number on error
int usr_sem_procure(usr_sem_t* sem) {
  semaphore_P(sem->kern_sem);
  return 0;
}
