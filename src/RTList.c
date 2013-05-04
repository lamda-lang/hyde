#include "RTList.h"

struct RTList {
  RTBase base;
  RTInteger32Bit length;
  RTValue element[];
};

RTList RTListCreate(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTList) + sizeof(RTValue) * length;
  RTList list = RTMemoryAlloc(size);
  if (list == NULL) {
    return NULL;
  }
  list->base = BASE(TYPE_LIST);
  list->length = length;
  return list;
}

void RTListDealloc(RTList list) {
  RTMemoryDealloc(list);
}

void RTListSetValueAtIndex(RTList list, RTValue value, RTInteger32Bit index) {
  list->element[index] = value;
}

RTValue RTListGetValueAtIndex(RTList list, RTInteger32Bit index) {
  return list->element[index];
}

RTBool RTListEqual(RTList list, RTList other) {
  if (list->length != other->length) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < list->length; index += 1) {
    if (RTValueEqual(list->element[index], other->element[index]) == FALSE) {
      return FALSE;
    }
  }
  return TRUE;
}

RTInteger64Bit RTListHash(RTList list) {
  return list->length;
}

void RTListEnumerateValues(RTList list, RTBlock block) {
  for (RTInteger32Bit index = 0; index < list->length; index += 1) {
    block(list->element[index]);
  }
}
