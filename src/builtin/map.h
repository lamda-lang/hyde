#ifndef MAP_H
#define MAP_H

#include <runtime.h>

Value *MapDecode(Byte **bytes, Error *error);
void MapRelease(Value *mapValue);

#endif
