#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Map *MapDecode(Byte **data, Exception *exception);

void MapDealloc(Value *mapValue);

void MapSetValueForKey(Map *map, Value *value, Value *key);

Integer64 MapHash(Value *mapValue);

void MapEnumerate(Value *mapValue, void (*block)(Value *value));

#endif
