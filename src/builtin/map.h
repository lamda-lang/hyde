#ifndef BUILTIN_MAP_H
#define BUILTIN_MAP_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *MapDecode(Byte **bytes, Error *error);
void MapDealloc(VALUE *mapValue);

#endif
