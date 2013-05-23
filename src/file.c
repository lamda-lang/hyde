#include <fcntl.h>
#include <unistd.h>
#include "file.h"

Data *FileRead(Char *path) {
  Data *data = DataCreate();
  if (data == NULL) {
    goto returnError;
  }
  int file = open(path, O_RDONLY);
  if (file == -1) {
    goto deallocData;
  }
  Byte buffer[512];
  ssize_t consumed = 0;
  do {
    consumed = read(file, buffer, sizeof(buffer));
    if (consumed == -1) {
      goto closeFile;
    }
    DataAppend(data, buffer, (Size)consumed);
  } while (consumed > 0);
  return data;

closeFile:
  close(file);
deallocData:
  DataDealloc(data);
returnError:
  return NULL;
}
