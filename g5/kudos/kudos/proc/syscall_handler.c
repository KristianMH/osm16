#include "syscall.h"
#include "syscall_handler.h"
#include "drivers/gcd.h"
#include "drivers/device.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#include "fs/vfs.h"


int syscall_read(int filehandle, void *buffer, int length) {
 if (filehandle == 1 || filehandle == 2 || filehandle < 0) {
    return ERROR_FILEHANDLE;
 }
 if (length < 0) {
   return ERROR_NEGATIVE_LENGTH;
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
 int ret = vfs_read(filehandle-2, buffer, length);
 if (ret >= 0) {
   return ret;
 }
 ret = -1;
 return ret;
}
  
int syscall_write(int filehandle, const void *buffer, int length) {
  if(length < 0){
    return ERROR_NEGATIVE_LENGTH;
  }
  if(filehandle == 0 || filehandle < 0){
    return ERROR_FILEHANDLE;
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
  int ret = vfs_write(filehandle-2, (void*)buffer, length);
  if (ret > 0) {
    return ret;
  }
  return -1;
}

int syscall_open(const char *pathname) {
  int ret;
  ret = vfs_open((char*)pathname);
  if (ret < 0) {
    return ret;
  }
  return ret+2;
}

int syscall_close(int filehandle) {
  int ret;
  if (filehandle < 3) {
    return VFS_INVALID_PARAMS;
  }
  ret = vfs_close(filehandle-2);
  if (ret < 0) {
    return -1;
  }
  return ret;
}

int syscall_create(const char *pathname, int size) {
  if (size < 0) {
    kprintf("negative size\n");
    return -1;
  }

  int ret = vfs_create((char *) pathname, size);
  if (ret != VFS_OK ) {
    kprintf("couldnt create file\n");
    return -1;
  }
  return ret;
}

int syscall_delete(const char *pathname) {
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
/* FIXME:  */
int syscall_filecount(const char *pathname) {
  if (pathname == NULL) {
    return -1;
  }
  int ret = vfs_filecount((char *)pathname);
  return ret;
}
/* FIXME:  */
int syscall_file(const char *pathname, int nth, char *buffer) {
  if (pathname == NULL || buffer == NULL || nth < 0) {
    return -1;
  }
  return vfs_file((char *) pathname, nth, buffer);
}
