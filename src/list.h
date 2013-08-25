#ifndef LIST_H
#define LIST_H

#include "runtime.h"

VALUE *ListDecode(Byte **bytes, VALUE **error);
void ListDealloc(VALUE *listValue);
Integer64 ListHash(VALUE *listValue);

#endif
