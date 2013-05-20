#include "RTList.h"

struct RTList {
  RTValue base;
  RTInteger32Bit length;
  RTValue *element[];
};

RTValue *RTListValueBridge(RTList *list) {
  return (RTValue *)list;
}

RTList *RTListDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data);
  RTSize size = sizeof(struct RTList) + sizeof(RTValue) * length;
  RTList *list = RTMemoryAlloc(size);
  if (list == NULL) {
    goto error;
  }
  list->base = RTValueInit(RTTypeList, RTFlagNone);
  list->length = length;
  return list;

error:
  return NULL;
}

void RTListDealloc(RTValue *list) {
  RTMemoryDealloc(list);
}

void RTListSetValueAtIndex(RTList *list, RTValue *value, RTInteger32Bit index) {
  list->element[index] = value;
}

RTValue *RTListGetValueAtIndex(RTList *list, RTInteger32Bit index) {
  return list->element[index];
}

RTInteger64Bit RTListHash(RTValue *list_RTList) {
  RTList *list = RTValueListBridge(list_RTList);
  return list->length;
}

void RTListEnumerate(RTValue *list_RTList, void (*block)(RTValue *value)) {
  RTList *list = RTValueListBridge(list_RTList);
  for (RTInteger32Bit index = 0; index < list->length; index += 1) {
    block(list->element[index]);
  }
}
