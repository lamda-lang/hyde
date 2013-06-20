#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapDecode(Byte **data, Error *error);
void MapFetch(Value *mapValue, Value **values);
void MapDealloc(Value *mapValue);
Integer64 MapHash(Value *mapValue);
void MapEnumerate(Value *mapValue, void (*callback)(Value *value));
Value *MapGetValueForKey(Value *mapValue, Value *key);
Value *MapEval(Value *mapValue, bool pure, Error *error);

#endif
