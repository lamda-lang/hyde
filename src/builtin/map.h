#ifndef BUILTIN_MAP_H
#define BUILTIN_MAP_H

#include <runtime.h>

Value *MapDecode(Byte **bytes);
void MapRelease(Map *map);
Bool MapEqual(Map *map, Map *other); 

#endif
