#include "RTList.h"
#include "RTMemory.h"
#include "RTValue.h"

union RTElement {
  RTValue value;
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

void RTListDealloc(RTList list) {
  RTMemoryDealloc(list);
}

void RTListSetRegisterIndexAtIndex(RTList list, RTInteger32Bit regIndex, RTInteger32Bit index) {
  list->element[index].index = regIndex;
}

RTValue RTListGetValueAtIndex(RTList list, RTInteger32Bit index) {
  return list->element[index].value;
}

void RTListFetch(RTList list, RTValue *reg) {
  for (RTIndex index = 0; index < list->length; index += 1) {
    RTInteger32Bit regIndex = list->element[index].index;
    list->element[index].value = reg[regIndex];
  }
}

RTBool RTListEqual(RTList list, RTList other) {
  if (list->length != other->length) {
    return FALSE;
  }
  for (RTIndex index = 0; index < list->length; index += 1) {
    if (list->element[index].value != other->element[index].value) {
      return FALSE;
    }
  }
  return TRUE;
}

RTInteger32Bit RTListHash(RTList list) {
  RTInteger32Bit hash = list->length;
  for (RTIndex index = 0; index < list->length; index += 1) {
    hash += RTValueHash(list->element[index].value);
  }
  return hash;
}

#ifdef RT_LIST_TEST

RTList FIXTURE_List(RTInteger32Bit length) {
  RTList list = RTListCreate(8);
  REQUIRE(list != NULL);
  return list;
}

RTValue FIXTURE_Value(RTList list) {
  RTValue value = RTValueCreateList(list);
  REQUIRE(value != NULL);
  return value;
}

void TEST_RTListCreate_Valid(void) {
  RTValue value = FIXTURE_Value(0);
  RTList list = RTListCreate(8);
  REQUIRE(list != NULL);
  ASSERT(list->length == 8);
  for (RTIndex index = 0; index < list->length; index += 1) {
    list->element[index].index = index;
    ASSERT(list->element[index].index == index);
    list->element[index].value = value;
    ASSERT(list->element[index].value == value);
  }
}

void TEST_RTListDealloc_Valid(void) {
  RTList list = FIXTURE_List(1);
  RTListDealloc(list);
}

void TEST_RTListSetRegisterIndexAtIndex_Valid(void) {
  RTList list = FIXTURE_List(1);
  RTListSetRegisterIndexAtIndex(list, 1, 0);
  ASSERT(list->element[0].index == 1);
}

void TEST_RTListGetValueAtIndex_Valid(void) {
  RTValue value = FIXTURE_Value(0);
  RTList list = FIXTURE_List(1);
  list->element[0].value = value;
  ASSERT(RTListGetValueAtIndex(list, 0) == value);
}

void TEST_RTListFetch_Valid(void) {
  RTValue value = FIXTURE_Value(0);
  RTList list = FIXTURE_List(1);
  RTValue reg[] = {value};
  list->element[0].index = 0;
  RTListFetch(list, reg);
  ASSERT(list->element[0].value == value);
}

void TEST_RTListEqual_LengthMismatch(void) {
  RTList list = FIXTURE_List(0);
  RTList other = FIXTURE_List(1);
  ASSERT(RTListEqual(list, other) == FALSE);
}

void TEST_RTListEqual_ContentMismatch(void) {
  RTList list = FIXTURE_List(1);
  RTList other = FIXTURE_List(1);
  list->element[0].value = FIXTURE_Value(other);
  other->element[0].value = FIXTURE_Value(list);
  ASSERT(RTListEqual(list, other) == FALSE);
}

void TEST_RTListEqual_Equal(void) {
  RTList list = FIXTURE_List(1);
  ASSERT(RTListEqual(list, list) == TRUE);
}

void TEST_RTListHash_Empty(void) {
  RTList list = FIXTURE_List(0);
  ASSERT(RTListHash(list) == 0);
}

void TEST_RTListHash_NonEmpty(void) {
  RTList list = FIXTURE_List(1);
  RTList other = FIXTURE_List(0);
  list->element[0].value = FIXTURE_Value(other);
  ASSERT(RTListHash(list) == 1);
}

void TEST_RTListHash_Self(void) {
  ASSERT(FALSE);
}

int main(void) {
  TEST_RTListCreate_Valid();
  TEST_RTListDealloc_Valid();
  TEST_RTListSetRegisterIndexAtIndex_Valid();
  TEST_RTListGetValueAtIndex_Valid();
  TEST_RTListFetch_Valid();
  TEST_RTListEqual_LengthMismatch();
  TEST_RTListEqual_ContentMismatch();
  TEST_RTListEqual_Equal();
  TEST_RTListHash_Empty();
  TEST_RTListHash_NonEmpty();
  TEST_RTListHash_Self();
}

#endif
