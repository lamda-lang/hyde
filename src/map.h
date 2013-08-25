#ifndef MAP_H
#define MAP_H

#include "runtime.h"

VALUE *MapDecode(Byte **bytes, VALUE **error);
VALUE *MapCreate(Integer32 count, VALUE **error);
void MapDealloc(VALUE *mapVALUE);
Integer64 MapHash(VALUE *mapVALUE);
void MapEnumerate(VALUE *mapVALUE, void (*callback)(VALUE *value));
VALUE *MapGetVALUEForKey(VALUE *mapVALUE, VALUE *key);

#endif
