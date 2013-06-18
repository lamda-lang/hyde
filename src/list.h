#ifndef LIST_H
#define LIST_H

#include "api.h"

List *ListCreate(Integer32 count, Error *error);

Value *ListValueBridge(List *list);

Value *ListDecode(Byte **bytes, Error *error);

void ListFetch(Value *listValue, Value **values);

void ListDealloc(Value *listValue);

void ListSetValueAtIndex(List *list, Value *value, Integer32 index);

Value *ListGetValueAtIndex(List *list, Integer32 index);

Integer64 ListHash(Value *listValue);

void ListEnumerate(Value *listValue, void (*callback)(Value *value));

Value *ListEval(Value *listValue, bool pure, Error *error);

#endif
