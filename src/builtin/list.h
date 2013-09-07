#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *ListDecode(Byte **bytes, Error *error);
void ListDealloc(VALUE *listValue);

#endif
