#ifndef BUILTIN_MAP_H
#define BUILTIN_MAP_H

#include <runtime.h>

typedef struct Map Map;

Map *MapDecode(Byte **bytes);
Map *MapEval(Map *map, Value *context);
Bool MapEqual(Map *map, Map *other); 
Size MapRelease(Map *map);

#endif
