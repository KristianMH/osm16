/*
 * Userland semaphores
 */
#ifndef KUDOS_USER_SEMAPHORE_H
#define KUDOS_USER_SEMAPHORE_H
#define USR_SEM_MAX_SEMAPHORES 128

#include "lib/libc.h"
#include "kernel/sleepq.h"
#include "kernel/spinlock.h"
#include "kernel/thread.h"
#include "kernel/interrupt.h"

typedef struct {
  int init;
  const char* name[20];
  int value;
  spinlock_t slock;
} usr_sem_t;

// Returns a pointer to a userland semaphore
usr_sem_t* usr_sem_open(const char* name, int value);

// destroys a userland semaphore, returns negative number on error
int usr_sem_destroy(usr_sem_t* sem);

// procure the userland semaphore, returns negative number on error
int usr_sem_procure(usr_sem_t* sem);

// vacate the userland semaphore, returns negative number on error
int usr_sem_vacate(usr_sem_t* sem);

void user_sem_init();

#endif
