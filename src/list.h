#ifndef LIST_H
#define LIST_H

#include "api.h"

Value *ListValueBridge(List *list);

List *ListDecode(Byte **bytes, Exception *exception);

void ListDealloc(Value *list);

void ListSetValueAtIndex(List *list, Value *value, Integer32 index);

Value *ListGetValueAtIndex(List *list, Integer32 index);

Integer64 ListHash(Value *list);

void ListEnumerate(Value *list, void (*block)(Value *value));

#endif
