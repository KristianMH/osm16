#include "write.h"
#include "drivers/gcd.h"
#include "drivers/device.h"
#include "syscall.h"
#include "kernel/assert.h"
#include "lib/libc.h"
#define ERROR_CANNOT_WRITE_TO_FILE -42
#define ERROR_NEGATIVE_LENGTH -666
#define ERROR_EMPTY_BUFFER -1337

int write(int filehandle, const void *buffer, int length){
  buffer = buffer;
  if(length < 0){
    return ERROR_NEGATIVE_LENGTH;
  }
  if(filehandle == 0){
    return ERROR_CANNOT_WRITE_TO_FILE;
  }
  device_t *device;
  gcd_t *gcd;
  device = device_get(TYPECODE_TTY, 0);
  KERNEL_ASSERT(device != NULL);
  gcd = (gcd_t *) device->generic_device;
  KERNEL_ASSERT(gcd != NULL);
  int written = gcd->write(gcd, buffer, length);
  return written;
}
