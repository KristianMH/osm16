
/*
 * System calls handling.
 */

#ifndef KUDOS_PROC_SYSCALL_HANDLER
#define KUDOS_PROC_SYSCALL_HANDLER

int syscall_open(const char *pathname);

int syscall_close(int filehandle);

int syscall_seek(int filehandle, int offset);

int syscall_read(int filehandle, void *buffer, int length);

int syscall_write(int filehandle, const void *buffer, int length);

int syscall_create(const char *pathname, int size);

int syscall_delete(const char *pathname);

int syscall_filecount(const char *pathname);

int syscall_file(const char *pathname, int nth, char *buffer);

#endif
