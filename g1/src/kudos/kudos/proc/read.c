#include "read.h"
#define ERROR_EMPTY_BUFFER -1337
#define ERROR_FILEHANDLE -8008135
#define ERROR_NEGATIVE_LENGTH -666

int read(int filehandle, void *buffer, int length){
  if(length < 0){
    return ERROR_NEGATIVE_LENGTH;
  }
  buffer = buffer;
  if(filehandle == 1 || filehandle == 2){
    return ERROR_FILEHANDLE;
  }
  return 0;
}
