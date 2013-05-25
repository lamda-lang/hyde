#include <fcntl.h>
#include <unistd.h>
#include "file.h"

struct File {
  int handle;
  Byte buffer[256];
};

File *FileOpen(Char *path) {
  File *file = MemoryAlloc(sizeof(File));
  if (file == NULL) {
    goto returnError;
  }
  int handle = open(path, O_RDWR);
  if (handle == -1) {
    goto deallocFile;
  }
  file->handle = handle;
  return file;

deallocFile:
  MemoryDealloc(file);
returnError:
  return NULL;
}

Status FileClose(File *file) {
  int status = close(file->handle);
  if (status == -1) {
    goto returnError;
  }
  MemoryDealloc(file);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

Data *FileRead(File *file) {
  Data *data = DataCreate();
  if (data == NULL) {
    goto returnError;
  }
  ssize_t consumed = 0;
  do {
    consumed = read(file->handle, file->buffer, sizeof(file->buffer));
    if (consumed == -1) {
      goto deallocData;
    }
    if (DataAppend(data, file->buffer, (Size)consumed) == StatusFailure) {
      goto deallocData;
    }
  } while (consumed > 0);
  return data;

deallocData:
  DataDealloc(data);
returnError:
  return NULL;
}

Status FileWrite(File *file, Data *data) {
  Byte *bytes = DataBytes(data);
  Size size = DataSize(data);
  ssize_t written = write(file->handle, bytes, size);
  if (written == -1 || (Size)written != size) {
    goto returnError;
  }
  return StatusSuccess;

returnError:
  return StatusFailure;
}
