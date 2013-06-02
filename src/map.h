#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Map *MapDecode(Byte **data, Error *error);

Integer32 MapCount(Map *map);

void MapSetValueForKey(Map *map, Value *value, Value *key);

void MapDealloc(Value *mapValue);

Integer64 MapHash(Value *mapValue);

void MapEnumerate(Value *mapValue, void (*block)(Value *value));

#endif
