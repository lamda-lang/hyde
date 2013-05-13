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
    return NULL;
  }
  list->base = RTValueInit(RTTypeList, RTFlagNone);
  list->length = length;
  return list;
}

void RTListDealloc(RTList *list) {
  RTMemoryDealloc(list);
}

void RTListSetValueAtIndex(RTList *list, RTValue *value, RTInteger32Bit index) {
  list->element[index] = value;
}

RTValue *RTListGetValueAtIndex(RTList *list, RTInteger32Bit index) {
  return list->element[index];
}

bool RTListEqual(RTList *list, RTList *other) {
  if (list->length != other->length) {
    return false;
  }
  for (RTInteger32Bit index = 0; index < list->length; index += 1) {
    /* missing */
  }
  return true;
}

RTInteger64Bit RTListHash(RTList *list) {
  return list->length;
}

void RTListEnumerateValues(RTList *list, RTBlock *block) {
  for (RTInteger32Bit index = 0; index < list->length; index += 1) {
    block(list->element[index]);
  }
}
