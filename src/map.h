#ifndef MAP_H
#define MAP_H

#include "api.h"

void *MapDecode(Byte **bytes, Value **error);
Value *MapCreate(Integer32 count, Value **error);
void MapDealloc(Value *mapValue);
Integer64 MapHash(Value *mapValue);
void MapEnumerate(Value *mapValue, void (*callback)(Value *value));
Value *MapGetValueForKey(Value *mapValue, Value *key);

#endif
