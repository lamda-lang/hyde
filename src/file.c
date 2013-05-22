#include "file.h"

#define BUFFER_SIZE 1024

Status FileRead(File file, Buffer *buffer) {
  Byte byte[BUFFER_SIZE];
  ssize_t consumed = 0;
  do {
    consumed = read(file, byte, BUFFER_SIZE);
    if (consumed == -1) {
      goto error;
    }
    BufferAppend(buffer, byte, (Size)consumed);
  } while (consumed > 0);
  return StatusSuccess;

error:
  return StatusFailure;
}

Status FileWrite(File file, Buffer *buffer) {
  Size size = BufferSize(buffer);
  Byte *bytes = BufferBytes(buffer);
  ssize_t written = write(file, bytes, size);
  if (written == -1 || (Size)written != size) {
    goto error;
  }
  return StatusSuccess;

error:
  return StatusFailure;
}
