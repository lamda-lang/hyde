#ifndef TYPE_H
#define TYPE_H

#include <runtime.h>

Value *TypeCreate(Integer32 count, Error *error);
Value *TypeDecode(Byte **bytes, Error *error);
void TypeDealloc(Value *typeValue);

#endif
