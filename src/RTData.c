#include "RTData.h"

struct RTData {
  RTByte *bytes;
  RTSize size;
};

RTData *RTDataCreate(void) {
  RTData *data = RTMemoryAlloc(sizeof(RTData));
  if (data == NULL) return NULL;
  data->size = 0;
  return data;
}

void RTDataDealloc(RTData *data) {
  RTMemoryDealloc(data->bytes);
  RTMemoryDealloc(data);
}

RTError RTDataAppend(RTData *data, RTByte *source, RTSize size) {
  RTByte *bytes = RTMemoryRealloc(data->bytes, data->size + size);
  if (bytes == NULL) return RTErrorOutOfMemory;
  RTByte *target = bytes + data->size;
  data->bytes = bytes;
  data->size += size;
  RTMemoryCopy(source, target, size);
  return RTErrorNone;
}

const RTByte *RTDataBytes(RTData *data) {
  return data->bytes;
}

RTSize RTDataSize(RTData *data) {
  return data->size;
}
