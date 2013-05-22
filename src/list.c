#include "list.h"

struct List {
  Value base;
  Integer32Bit length;
  Value *element[];
};

Value *ListValueBridge(List *list) {
  return (Value *)list;
}

List *ListDecode(Byte **data) {
  Integer32Bit length = DecodeVBRInteger32Bit(data);
  Size size = sizeof(struct List) + sizeof(Value) * length;
  List *list = MemoryAlloc(size);
  if (list == NULL) {
    goto error;
  }
  list->base = ValueInit(TypeList, FlagNone);
  list->length = length;
  return list;

error:
  return NULL;
}

void ListDealloc(Value *list) {
  MemoryDealloc(list);
}

void ListSetValueAtIndex(List *list, Value *value, Integer32Bit index) {
  list->element[index] = value;
}

Value *ListGetValueAtIndex(List *list, Integer32Bit index) {
  return list->element[index];
}

Integer64Bit ListHash(Value *list_List) {
  List *list = ValueListBridge(list_List);
  return list->length;
}

void ListEnumerate(Value *list_List, void (*block)(Value *value)) {
  List *list = ValueListBridge(list_List);
  for (Integer32Bit index = 0; index < list->length; index += 1) {
    block(list->element[index]);
  }
}
