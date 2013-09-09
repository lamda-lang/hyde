#ifndef LIST_H
#define LIST_H

#include <runtime.h>

Value *ListDecode(Byte **bytes, Error *error);
Bool ListEqual(Value *listValue, Value *otherValue);
void ListRelease(Value *listValue);

#endif
