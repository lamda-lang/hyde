#include "RTFile.h"

#define BUFFER_SIZE 1024

RTError RTFileRead(RTFile file, RTData *data) {
  RTByte buffer[BUFFER_SIZE];
  ssize_t consumed = 0;
  do {
    consumed = read(file, buffer, BUFFER_SIZE);
    if (consumed == -1) return RTErrorReadFile;
    RTDataAppend(data, buffer, (RTSize)consumed);
  } while (consumed > 0);
  return RTErrorNone;
}

RTError RTFileWrite(RTFile file, void *buffer, RTSize size) {
  ssize_t written = write(file, buffer, size);
  if (written == -1 || (RTSize)written != size) return RTErrorWriteFile;
  return RTErrorNone;
}
