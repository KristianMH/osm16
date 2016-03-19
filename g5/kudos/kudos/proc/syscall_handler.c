#include "proc/syscall.h"
#include "proc/syscall_handler.h"
#include "drivers/gcd.h"
#include "drivers/device.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#include "fs/vfs.h"
#include "proc/process.h"
#include "kernel/thread.h"
#include "vm/mips32/mem.h"


int syscall_read(int filehandle, void *buffer, int length) {
 if (filehandle == 1 || filehandle == 2 || filehandle < 0) {
    return ERROR_FILEHANDLE;
 }
 if (length < 0) {
   return ERROR_NEGATIVE_LENGTH;
 }
 if (!IN_USERLAND(buffer) || !IN_USERLAND(buffer + length)) {
   KERNEL_PANIC("SEGFAULT\n");
 }
 if (filehandle == 0) {
   device_t *device;
   gcd_t *gcd;
   device = device_get(TYPECODE_TTY, 0);
   KERNEL_ASSERT(device != NULL);
   gcd = (gcd_t *) device->generic_device;
   KERNEL_ASSERT(gcd != NULL);
   int read = gcd->read(gcd, buffer, length);
   return read;
 }
 int is_in_process_list = process_find_index(filehandle);
 if (is_in_process_list < 0 ) {
   return -1;
 }
 
 int ret = vfs_read(filehandle-2, buffer, length);
 return ret;
}
  
int syscall_write(int filehandle, const void *buffer, int length) {
  if(length < 0){
    return ERROR_NEGATIVE_LENGTH;
  }
  if(filehandle == 0 || filehandle < 0){
    return ERROR_FILEHANDLE;
  }
  if (!IN_USERLAND(buffer) || !IN_USERLAND(buffer + length)) {
    KERNEL_PANIC("SEGFAULT\n");
  }
  if (filehandle == 1 || filehandle == 2) {
    device_t *device;
    gcd_t *gcd;
    device = device_get(TYPECODE_TTY, 0);
    KERNEL_ASSERT(device != NULL);
    gcd = (gcd_t *) device->generic_device;
    KERNEL_ASSERT(gcd != NULL);
    int written = gcd->write(gcd, buffer, length);
    return written;
  }
  
  int is_in_process_list = process_find_index(filehandle-2);
  if (is_in_process_list < 0 ) {
    kprintf("File is not open \n");
    return -1;
  }
  
  int ret = vfs_write(filehandle-2, (void*)buffer, length);
  return ret;
}

int syscall_open(const char *pathname) {
  if (pathname == NULL) return -1;
  int filehandle;
  process_control_block_t* block = process_get_current_process_entry();
  // checks for free space in process list
  if (block->free_index < 0) return -1;
  filehandle = vfs_open((char*)pathname);
  // vfs_open error
  if (filehandle < 0) return filehandle;
  // set offset, update free index and insert into list.
  filehandle = filehandle+2;
  block->openfiles[block->free_index] = filehandle;
  int free_index = process_find_free_index();
  block->free_index = free_index;
  return filehandle;
}

int syscall_close(int filehandle) {
  int ret;
  if (filehandle < 3) {
    return VFS_INVALID_PARAMS;
  }
  int index = process_find_index(filehandle);
  if (index < 0 ) {
    return -1;
  }
  ret = vfs_close(filehandle-2);
  if (ret < 0) {
    return -1;
  }
  process_get_current_process_entry()->free_index = index;
  process_get_current_process_entry()->openfiles[index] = 0;
  return ret;
}

int syscall_create(const char *pathname, int size) {
  if (size < 0) {
    kprintf("negative size\n");
    return -1;
  }
  if (pathname == NULL) return -1;
  int ret = vfs_create((char *) pathname, size);
  if (ret != VFS_OK ) {
    kprintf("couldnt create file\n");
    return -1;
  }
  return ret;
}

int syscall_delete(const char *pathname) {
  if (pathname == NULL) return -1;
  int ret =  vfs_remove((char *) pathname);
  return ret;
}

int syscall_seek(int filehandle, int offset) {
  if (filehandle < 0 || offset < 0) {
    return -1;
  }
  int ret = vfs_seek(filehandle-2, offset);
  return ret;
}

int syscall_filecount(const char *pathname) {
  if (pathname == NULL) {
    return -1;
  }
  int ret = vfs_filecount((char *)pathname);
  return ret;
}

int syscall_file(const char *pathname, int nth, char *buffer) {
  if (pathname == NULL || buffer == NULL || nth < 0) {
    return -1;
  }
  return vfs_file((char *) pathname, nth, buffer);
}
