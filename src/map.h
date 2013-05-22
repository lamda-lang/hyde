#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Map *MapDecode(Byte **data);

void MapDealloc(Value *map_Map);

void MapSetValueForKey(Map *map, Value *value, Value *key);

Integer64Bit MapHash(Value *map_Map);

void MapEnumerate(Value *map_Value, void (*block)(Value *value));

#endif
