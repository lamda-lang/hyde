#ifndef LIST_H
#define LIST_H

#include "api.h"

void *ListDecode(Byte **bytes, VALUE **error);
VALUE *ListCreate(Integer32 count, VALUE **error);
void ListDealloc(VALUE *listVALUE);
void ListSetVALUEAtIndex(VALUE *listVALUE, VALUE *value, Integer32 index);
VALUE *ListGetVALUEAtIndex(VALUE *listVALUE, Integer32 index);
Integer64 ListHash(VALUE *listVALUE);
void ListEnumerate(VALUE *listVALUE, void (*callback)(VALUE *value));

#endif
