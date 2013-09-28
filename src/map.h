#ifndef MAP_H
#define MAP_H

#include "runtime.h"

Size MapSize(Map *map);
Size MapEncode(Map *map, Byte **bytes);
Map *MapDecode(Byte **bytes, Error *error);
Value *MapEval(Value *value, Map *map, Value *context, Error *error);
Bool MapEqual(Map *map, Map *other); 
Size MapRelease(Map *map);

#endif
