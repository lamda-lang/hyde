#ifndef LIST_H
#define LIST_H

#include "api.h"

Value *ListValueBridge(List *list);

List *ListDecode(Byte **bytes, Error *error);

void ListFetch(List *list, Value **values, Byte **bytes);

void ListDealloc(Value *listValue);

Value *ListGetValueAtIndex(List *list, Integer32 index);

Integer64 ListHash(Value *listValue);

void ListEnumerate(Value *listValue, void (*block)(Value *value));

#endif
