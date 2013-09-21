#ifndef MAP_H
#define MAP_H

#include "runtime.h"

Map *MapDecode(Byte **bytes);
Map *MapEval(Map *map, Value *context);
Bool MapEqual(Map *map, Map *other); 
Size MapRelease(Map *map);

#endif
