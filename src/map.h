#ifndef MAP_H
#define MAP_H

#include "runtime.h"

VALUE *MapDecode(Byte **bytes, VALUE **error);
void MapDealloc(VALUE *mapValue);
Integer64 MapHash(VALUE *mapValue);

#endif
