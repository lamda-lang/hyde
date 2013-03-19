#include "RTHash.h"
#include "RTList.h"
#include "RTMemory.h"
#include "RTPrimitive.h"

union RTElement {
  RTPrimitive primitive;
  RTInteger32Bit index;
};

struct RTList {
  RTInteger32Bit length;
  union RTElement element[];
};

RTList RTListCreate(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTList) + SIZE_OF(union RTElement, length);
  RTList list = RTMemoryAlloc(size);
  if (list == NULL) {
    return NULL;
  }
  list->length = length;
  return list;
}

void RTListDealloc(void *list_RTList) {
  RTMemoryDealloc(list_RTList);
}

void RTListSetRegisterIndexAtIndex(RTList list, RTInteger32Bit regIndex, RTInteger32Bit index) {
  list->element[index].index = regIndex;
}

RTPrimitive RTListGetPrimitiveAtIndex(RTList list, RTInteger32Bit index) {
  return list->element[index].primitive;
}

void RTListFetch(RTList list, RTPrimitive *reg) {
  for (RTIndex index = 0; index < list->length; index += 1) {
    RTInteger32Bit elementIndex = list->element[index].index;
    list->element[index].primitive = reg[elementIndex];
  }
}

RTBool RTListEqual(void *list_RTList, void *other_RTList) {
  RTList list = list_RTList;
  RTList other = other_RTList;
  if (list->length != other->length) {
    return FALSE;
  }
  for (RTIndex index = 0; index < list->length; index += 1) {
    if (list->element[index].primitive != other->element[index].primitive) {
      return FALSE;
    }
  }
  return TRUE;
}

RTInteger32Bit RTListHash(void *list_RTList) {
  RTList list = list_RTList;
  RTInteger32Bit hash = RTHashValue(&list->length, sizeof(RTInteger32Bit));
  for (RTIndex index = 0; index < list->length; index += 1) {
    hash += RTPrimitiveHash(list->element[index].primitive);
  }
  return hash;
}

#ifdef RT_LIST_TEST

int main(void) {

}

#endif
