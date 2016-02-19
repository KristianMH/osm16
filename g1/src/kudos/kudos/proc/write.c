#include "write.h"
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
  return 0;
}
