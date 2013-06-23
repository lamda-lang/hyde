#ifndef MAP_H
#define MAP_H

#include "api.h"

void *MapDecode(Byte **bytes, Error *error);
Value *MapEval(void *data, Code *code, bool pure, Error *error);
void MapDealloc(Value *mapValue);
Integer64 MapHash(Value *mapValue);
void MapEnumerate(Value *mapValue, void (*callback)(Value *value));
Value *MapGetValueForKey(Value *mapValue, Value *key);

#endif
