#include "RTFile.h"

#define BUFFER_SIZE 1024

RTStatus RTFileRead(RTFile file, RTBuffer *buffer) {
  RTByte byte[BUFFER_SIZE];
  ssize_t consumed = 0;
  do {
    consumed = read(file, byte, BUFFER_SIZE);
    if (consumed == -1) {
      goto error;
    }
    RTBufferAppend(buffer, byte, (RTSize)consumed);
  } while (consumed > 0);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

RTStatus RTFileWrite(RTFile file, RTBuffer *buffer) {
  RTSize size = RTBufferSize(buffer);
  RTByte *bytes = RTBufferBytes(buffer);
  ssize_t written = write(file, bytes, size);
  if (written == -1 || (RTSize)written != size) {
    goto error;
  }
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}
