#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Value *MapDecode(Byte **data, Error *error);

void MapFetch(Value *mapValue, Value **values);

void MapDealloc(Value *mapValue);

Integer64 MapHash(Value *mapValue);

void MapEnumerate(Value *mapValue, void (*callback)(Value *value));

Value *MapGetValueForKey(Map *map, Value *key);

Value *MapEval(Value *mapValue, Error *error);

#endif
