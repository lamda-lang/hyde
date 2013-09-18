#ifndef BUILTIN_MAP_H
#define BUILTIN_MAP_H

#include <runtime.h>

typedef struct Map Map;

Map *MapDecode(Byte **bytes);
Value *MapEval(Map *map, Value *context);
Value *MapEqual(Map *map, Map *other); 
Size MapRelease(Map *map);

#endif
