#ifndef LIST_H
#define LIST_H

#include "api.h"

VALUE *ListDecode(Byte **bytes, Error *error);
void ListDealloc(VALUE *listValue);

#endif
