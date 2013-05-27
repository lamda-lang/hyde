#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Map *MapDecode(Byte **data, Exception *exception);

void MapDealloc(Value *map);

void MapSetValueForKey(Map *map, Value *value, Value *key);

Integer64 MapHash(Value *map);

void MapEnumerate(Value *map, void (*block)(Value *value));

#endif
