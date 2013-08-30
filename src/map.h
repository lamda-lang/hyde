#ifndef MAP_H
#define MAP_H

#include "runtime.h"

VALUE *MapDecode(Byte **bytes, Error *error);
void MapDealloc(VALUE *mapValue);

#endif
