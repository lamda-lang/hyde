#ifndef MAP_H
#define MAP_H

#include "runtime.h"

Size MapSize(Map *map);
Map *MapDecode(Byte **bytes, Error *error);
Map *MapEval(Map *map, Value *context, Error *error);
Bool MapEqual(Map *map, Map *other); 
Size MapRelease(Map *map);

#endif
