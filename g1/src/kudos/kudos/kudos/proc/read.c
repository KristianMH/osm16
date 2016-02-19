#include "read.h"
#include "drivers/gcd.h"
#include "drivers/device.h"
#include "syscall.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#define ERROR_EMPTY_BUFFER -1337
#define ERROR_FILEHANDLE -8008135
#define ERROR_NEGATIVE_LENGTH -666

int read(int filehandle, void *buffer, int length){
  device_t *device;
  gcd_t *gcd;
  if(length < 0){
    return ERROR_NEGATIVE_LENGTH;
  }
  buffer = buffer;
  if(filehandle == 1 || filehandle == 2){
    return ERROR_FILEHANDLE;
  }
  device = device_get(TYPECODE_TTY, 0);
  KERNEL_ASSERT(device != NULL);
  gcd = (gcd_t *) device->generic_device;
  KERNEL_ASSERT(gcd != NULL);
  int read = gcd->read(gcd, buffer, length);
  return read;
}
