/*
 * Userland semaphore implementation.
 */

#include "usr_sem.h"

static spinlock_t usr_sem_table_slock;
// userland semaphore array
usr_sem_t sem_array[USR_SEM_MAX_SEMAPHORES];

// finds a free entry in array, negative value on no space
int find_sem_space() {
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    if (sem_array[i].init < 0) {
      return i;
    }
  }
  return -1;
}

void user_sem_init() {
  spinlock_reset(&usr_sem_table_slock);
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    sem_array[i].init = -1;
  }
}
// returns an existing semaphore with same name.
int compare_sem_name(const char* name) {
  for (int i = 0; i < USR_SEM_MAX_SEMAPHORES; i++) {
    if (*sem_array[i].name == name) {
      return i;
    }
  }
  return -1;
}

// Returns a pointer to a userland semaphore
usr_sem_t* usr_sem_open(const char* name, int value) {
  int space = find_sem_space();
  int same_name = compare_sem_name(name);
  if (space < 0) {
    kprintf("no space for sem");
    return 0;
  }
  if (value < 0) {
    if (same_name < 0) {
      return NULL;
    }
    return &sem_array[same_name];
  }
  if (value >= 0) {
    if (same_name > 0) {
      return NULL;
    }    
  }
  *sem_array[space].name = name;
  sem_array[space].value = value;
  sem_array[space].init = 0;
  return &sem_array[space];
}

// destroys a userland semaphore, returns negative number on error
int usr_sem_destroy(usr_sem_t* sem) {
  sem->init = -1;
  *sem->name = (const char*)NULL;
  sem->value = (int)NULL;
  return 0;
}

// procure the userland semaphore, returns negative number on error
int usr_sem_vacate(usr_sem_t* sem) {
  sem->value++;
  if (sem->value <= 0) {
    sleepq_wake(sem);
  }
  return 0;
}

// vacate the userland semaphore, returns negative number on error
int usr_sem_procure(usr_sem_t* sem) {
  sem->value--;
  if (sem->value < 0) {
    sleepq_add(sem);
    
  }
  return 0;
}
