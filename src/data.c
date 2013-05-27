#include "data.h"

struct Data {
    Byte *bytes;
    Size size;
};

Data *DataCreate(Exception *exception) {
    Size size = sizeof(Data);
    Data *data = MemoryAlloc(size, exception);
    if (data == NULL) {
        goto returnError;
    }
    data->bytes = NULL;
    data->size = 0;
    return data;

returnError:
    return NULL;
}

void DataDealloc(Data *data) {
    MemoryDealloc(data->bytes);
    MemoryDealloc(data);
}

Status DataAppendBytes(Data *data, Byte *bytes, Size size, Exception *exception) {
    Byte *buffer = MemoryRealloc(data->bytes, data->size + size, exception);
    if (buffer == NULL) {
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
