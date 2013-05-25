#include "data.h"

struct Data {
  Byte *bytes;
  Size size;
};

Data *DataCreate(void) {
  Size size = sizeof(Data);
  Data *data = MemoryAlloc(size);
  if (data == NULL) {
    ExceptionRaise(ExceptionOutOfMemory);
    goto returnError;
  }
  data->bytes = NULL;
  data->size = 0;
  return data;

error:
  return NULL;
}

void DataDealloc(Data *data) {
  MemoryDealloc(data->bytes);
  MemoryDealloc(data);
}

Status DataAppendBytes(Data *data, Byte *bytes, Size size) {
  Byte *buffer = MemoryRealloc(data->bytes, data->size + size);
  if (buffer == NULL) {
    ExceptionRaise(ExceptionOutOfMemory);
    goto returnError;
  }
  MemoryCopy(bytes, buffer + data->size, size);
  data->bytes = buffer;
  data->size += size;
  return StatusSuccess;

returnError:
  return StatusFailure;
}

Byte *DataBytes(Data *data) {
  return data->bytes;
}

Size DataSize(Data *data) {
  return data->size;
}
