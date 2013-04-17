#include "RTList.h"

struct RTList {
  RTInteger32Bit length;
  RTValue element[];
};

RTList RTListCreate(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTList) + SIZE_OF(RTValue, length);
  RTList list = RTMemoryAlloc(size);
  if (list == NULL) {
    return NULL;
  }
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
