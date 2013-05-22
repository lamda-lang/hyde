#ifndef LIST_H
#define LIST_H

#include "runtime.h"

Value *ListValueBridge(List *list);

List *ListDecode(Byte **data);

void ListDealloc(Value *list_List);

void ListSetValueAtIndex(List *list, Value *value, Integer32Bit index);

Value *ListGetValueAtIndex(List *list, Integer32Bit index);

Integer64Bit ListHash(Value *list_Value);

void ListEnumerate(Value *list_List, void (*block)(Value *value));

#endif
