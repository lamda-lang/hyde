#ifndef TYPE_H
#define TYPE_H

#include <runtime.h>

VALUE *TypeCreate(Integer32 count, Error *error);
VALUE *TypeDecode(Byte **bytes, Error *error);
void TypeDealloc(VALUE *typeValue);

#endif
