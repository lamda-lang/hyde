#include "RTFile.h"

#define BUFFER_SIZE 1024

RTError RTFileRead(RTFile file, RTBuffer *buffer) {
  RTByte byte[BUFFER_SIZE];
  ssize_t consumed = 0;
  do {
    consumed = read(file, byte, BUFFER_SIZE);
    if (consumed == -1) return RTErrorReadFile;
    RTBufferAppend(buffer, byte, (RTSize)consumed);
  } while (consumed > 0);
  return RTErrorNone;
}

RTError RTFileWrite(RTFile file, void *buffer, RTSize size) {
  ssize_t written = write(file, buffer, size);
  if (written == -1 || (RTSize)written != size) return RTErrorWriteFile;
  return RTErrorNone;
}
