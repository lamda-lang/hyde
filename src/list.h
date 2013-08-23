#ifndef LIST_H
#define LIST_H

#include "api.h"

void *ListDecode(Byte **bytes, Value **error);
Value *ListCreate(Integer32 count, Value **error);
void ListDealloc(Value *listValue);
void ListSetValueAtIndex(Value *listValue, Value *value, Integer32 index);
Value *ListGetValueAtIndex(Value *listValue, Integer32 index);
Integer64 ListHash(Value *listValue);
void ListEnumerate(Value *listValue, void (*callback)(Value *value));

#endif
