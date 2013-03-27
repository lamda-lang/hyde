#include "RTList.h"
#include "RTMemory.h"
#include "RTValue.h"

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
  for (RTIndex index = 0; index < list->length; index += 1) {
    if (list->element[index] != other->element[index]) {
      return FALSE;
    }
  }
  return TRUE;
}

RTInteger32Bit RTListHash(RTList list, RTBool recursive) {
  if (recursive == FALSE) {
    return list->length;;
  }
  RTInteger32Bit hash = list->length;
  for (RTIndex index = 0; index < list->length; index += 1) {
    hash += RTValueHash(list->element[index], FALSE);
  }
  return hash;
}

#ifdef RT_LIST_TEST

RTList FIXTURE_List(RTInteger32Bit length) {
  RTList list = RTListCreate(length);
  REQUIRE(list != NULL);
  return list;
}

RTValue FIXTURE_Value(RTList list) {
  RTValue value = RTValueCreate();
  REQUIRE(value != NULL);
  RTValueSetList( value, list);
  return value;
}

void TEST_RTListCreate_Valid(void) {
  RTList list = RTListCreate(8);
  RTValue value = FIXTURE_Value(list);
  REQUIRE(list != NULL);
  ASSERT(list->length == 8);
  for (RTIndex index = 0; index < list->length; index += 1) {
    list->element[index] = value;
    ASSERT(list->element[index] == value);
  }
}

void TEST_RTListDealloc_Valid(void) {
  RTList list = FIXTURE_List(1);
  RTListDealloc(list);
}

void TEST_RTListGetValueAtIndex_Valid(void) {
  RTList list = FIXTURE_List(1);
  RTValue value = FIXTURE_Value(list);
  list->element[0] = value;
  ASSERT(RTListGetValueAtIndex(list, 0) == value);
}

void TEST_RTListEqual_LengthMismatch(void) {
  RTList list = FIXTURE_List(0);
  RTList other = FIXTURE_List(1);
  ASSERT(RTListEqual(list, other) == FALSE);
}

void TEST_RTListEqual_ContentMismatch(void) {
  RTList list = FIXTURE_List(1);
  RTList other = FIXTURE_List(1);
  list->element[0] = FIXTURE_Value(other);
  other->element[0] = FIXTURE_Value(list);
  ASSERT(RTListEqual(list, other) == FALSE);
}

void TEST_RTListEqual_Equal(void) {
  RTList list = FIXTURE_List(1);
  ASSERT(RTListEqual(list, list) == TRUE);
}

void TEST_RTListHash_Empty(void) {
  RTList list = FIXTURE_List(0);
  ASSERT(RTListHash(list, TRUE) == 0);
}

void TEST_RTListHash_NonEmpty(void) {
  RTList list = FIXTURE_List(1);
  RTList other = FIXTURE_List(0);
  list->element[0] = FIXTURE_Value(other);
  ASSERT(RTListHash(list, TRUE) == 1);
}

void TEST_RTListHash_Self(void) {
  RTList list = FIXTURE_List(1);
  list->element[0] = FIXTURE_Value(list);
  ASSERT(RTListHash(list, TRUE) == 2);
}

int main(void) {
  TEST_RTListCreate_Valid();
  TEST_RTListDealloc_Valid();
  TEST_RTListGetValueAtIndex_Valid();
  TEST_RTListEqual_LengthMismatch();
  TEST_RTListEqual_ContentMismatch();
  TEST_RTListEqual_Equal();
  TEST_RTListHash_Empty();
  TEST_RTListHash_NonEmpty();
  TEST_RTListHash_Self();
}

#endif
