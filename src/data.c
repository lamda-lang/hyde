#include "data.h"

struct Data {
    Byte *bytes;
    Size size;
};

Data *DataCreate(Error *error) {
    Data *data = MemoryAlloc(sizeof(Data), error);
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
    if (data != NULL) {
	MemoryDealloc(data->bytes);
	MemoryDealloc(data);
    }
}

Status DataAppendBytes(Data *data, Byte *bytes, Size size, Error *error) {
    Byte *buffer = MemoryRealloc(data->bytes, data->size + size, error);
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
