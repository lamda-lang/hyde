#ifndef LIST_H
#define LIST_H

#include "api.h"

Value *ListCreate(Integer32 count, Error *error);
Value *ListDecode(Byte **bytes, Error *error);
void ListFetch(Value *listValue, Value **values);
void ListDealloc(Value *listValue);
void ListSetValueAtIndex(Value *listValue, Value *value, Integer32 index);
Value *ListGetValueAtIndex(Value *listValue, Integer32 index);
Integer64 ListHash(Value *listValue);
void ListEnumerate(Value *listValue, void (*callback)(Value *value));
Value *ListEval(Value *listValue, bool pure, Error *error);

#endif
