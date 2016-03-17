/*
 * Process startup.
 */

#ifndef KUDOS_PROC_PROCESS
#define KUDOS_PROC_PROCESS

#include "lib/types.h"
#include "vm/memory.h"
#include "kernel/config.h"

#define PROCESS_PTABLE_FULL  -1
#define PROCESS_ILLEGAL_JOIN -2

#define PROCESS_MAX_FILELENGTH 256
#define PROCESS_MAX_PROCESSES  128
#define PROCESS_MAX_FILES      10

typedef int process_id_t;

typedef enum {
    PROCESS_FREE,
    PROCESS_RUNNING,
    PROCESS_ZOMBIE
} process_state_t;

typedef struct {
/* We need to keep track of a process' state to make sure calls to eg. `join` do
   the right thing. */
    process_state_t state;

/* A parent should be able to get a child's return value after it exits, so we
   store it here. */
    int retval;

/* Only a process' parent should be able to interface with it. */
    process_id_t parent;

/* Initial contents of some registers. */
  virtaddr_t entry_point;
  virtaddr_t stack_top;

  int openfiles[PROCESS_MAX_FILES];
  int free_index;
} process_control_block_t;

/* find a free index in openfiles table */
int process_find_free_index();
/* finds the index of the filehandle in openfiles table  */
int process_find_index(int value);

/* closes all openfiles from openfiles table */
int process_close_open_files();

/* Load and run the executable as a new process in a new thread
   Argument: executable file name; Returns: process ID of the new process */
process_id_t process_spawn(char const* executable, char const **argv);

/* Stop the current process and the kernel thread in which it runs
   Argument: return value */
void process_exit(int retval);

/* Wait for the given process to terminate, return its return value,
   and mark the process-table entry as free */
int process_join(process_id_t pid);

/* Initialize process table.
   Should be called before any other process-related calls */
void process_init(void);

/* Return PID of current process. */
process_id_t process_get_current_process(void);

/* Return PCB of current process. */
process_control_block_t *process_get_current_process_entry(void);

#endif
