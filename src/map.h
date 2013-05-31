#ifndef MAP_H
#define MAP_H

#include "api.h"

Value *MapValueBridge(Map *map);

Map *MapDecode(Byte **data, Error *error);

void MapFetch(Map *map, Value **values, Byte **bytes);

void MapDealloc(Value *mapValue);

Integer64 MapHash(Value *mapValue);

void MapEnumerate(Value *mapValue, void (*block)(Value *value));

#endif
