#ifndef LIST_H
#define LIST_H

#include "api.h"

void *ListDecode(Byte **bytes, Error *error);
Value *ListEval(void *data, Code *code, Value **context, bool pure, Error *error);
Value *ListCreate(Integer32 count, Error *error);
void ListDealloc(Value *listValue);
void ListSetValueAtIndex(Value *listValue, Value *value, Integer32 index);
Value *ListGetValueAtIndex(Value *listValue, Integer32 index);
Integer64 ListHash(Value *listValue);
void ListEnumerate(Value *listValue, void (*callback)(Value *value));

#endif
