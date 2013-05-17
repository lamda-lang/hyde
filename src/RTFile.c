#include "RTFile.h"

#define BUFFER_SIZE UINT8_MAX

RTError RTFileRead(RTFile file, RTData *data) {
  RTByte buffer[BUFFER_SIZE];
  ssize_t consumed = 0;
  do {
    consumed = read(file, buffer, BUFFER_SIZE);
    if (consumed == -1) return RTErrorFileRead;
    RTDataAppend(data, buffer, (RTSize)consumed);
  } while (consumed > 0);
  return RTErrorNone;
}
