#include "RTValue.h"

typedef enum {
  IDENTIFIER = 0,
  INTEGER = 1,
  LIST = 2,
  MAP = 3,
  STRING = 4
} RTType;

struct RTValue {
  RTPrimitive primitive;
  RTType type;
  RTBool initialized;
};

RTValue RTValueCreate() {
  RTValue value = RTMemoryAlloc(sizeof(struct RTValue));
  if (value == NULL) {
    return NULL;
  }
  value->initialized = FALSE;
  return value;
}

void RTValueDealloc(RTValue value) {
  if (value->initialized == TRUE) {
    switch (value->type) {
    case IDENTIFIER:
      RTIdentifierDealloc(value->primitive.id);
      break;
    case INTEGER:
      RTIntegerDealloc(value->primitive.integer);
      break;
    case LIST:
      RTListDealloc(value->primitive.list);
      break;
    case MAP:
      RTMapDealloc(value->primitive.map);
      break;
    case STRING:
      RTStringDealloc(value->primitive.string);
      break;
    }
  }
  RTMemoryDealloc(value);
}
void RTValueSetIdentifier(RTValue value, RTIdentifier id) {
  value->primitive.id = id;
  value->type = IDENTIFIER;
  value->initialized = TRUE;
}

void RTValueSetInteger(RTValue value, RTInteger integer) {
  value->primitive.integer = integer;
  value->type = INTEGER;
  value->initialized = TRUE;
}

void RTValueSetList(RTValue value, RTList list) {
  value->primitive.list = list;
  value->type = LIST;
  value->initialized = TRUE;
}

void RTValueSetMap(RTValue value, RTMap map) {
  value->primitive.map = map;
  value->type = MAP;
  value->initialized = TRUE;
}

void RTValueSetString(RTValue value, RTString string) {
  value->primitive.string = string;
  value->type = STRING;
  value->initialized = TRUE;
}

RTPrimitive RTValueGetPrimitive(RTValue value) {
  return value->primitive;
}

RTInteger64Bit RTValueHash(RTValue value) {
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierHash(value->primitive.id);
  case INTEGER:
    return RTIntegerHash(value->primitive.integer);
  case LIST:
    return RTListHash(value->primitive.list);
  case MAP:
    return RTMapHash(value->primitive.map);
  case STRING:
    return RTStringHash(value->primitive.string);
  }
}

RTBool RTValueEqual(RTValue value, RTValue other) {
  if (value->type != other->type) {
    return FALSE;
  }
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierEqual(value->primitive.id, other->primitive.id);
  case INTEGER:
    return RTIntegerEqual(value->primitive.integer, other->primitive.integer);
  case LIST:
    return RTListEqual(value->primitive.list, other->primitive.list);
  case MAP:
    return RTMapEqual(value->primitive.map, other->primitive.map);
  case STRING:
    return RTStringEqual(value->primitive.string, other->primitive.string);
  }
}

#ifdef RT_VALUE_TEST

static RTValue FIXTURE_Value(void) {
  RTValue value = RTValueCreate();
  REQUIRE(value != NULL);
  return value;
}

static RTValue FIXTURE_ValueInitialized(RTIdentifier id) {
  RTValue value = RTValueCreate();
  REQUIRE(value != NULL);
  RTValueSetIdentifier(value, id);
  return value;
}

static RTIdentifier FIXTURE_Identifier(void) {
  RTByte data[] = {0X01, 0X02};
  RTByte *alias = data;
  RTIdentifier id = RTIdentifierDecode(&alias);
  REQUIRE(id != NULL);
  return id;
}

static void AFTER_Value(RTValue value) {
  RTValueDealloc(value);
}

static void TEST_RTValueCreate_Valid(void) {
  RTValue value = RTValueCreate();
  REQUIRE(value != NULL);
  ASSERT(value->initialized == FALSE);
  AFTER_Value(value);
}

static void TEST_RTValueDealloc_NotInitialized(void) {
  RTValue value = FIXTURE_Value();
  RTValueDealloc(value);
}

static void TEST_RTValueDealloc_Initialized(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTValue value = FIXTURE_ValueInitialized(id);
  RTValueDealloc(value);
}

static void TEST_RTValueSetIdentifier_Valid(void) {
  RTValue value = FIXTURE_Value();
  RTValueSetIdentifier(value, NULL);
  ASSERT(value->type == IDENTIFIER);
  ASSERT(value->primitive.id == NULL);
  ASSERT(value->initialized == TRUE);
  AFTER_Value(value);
}

static void TEST_RTValueSetInteger_Valid(void) {
  RTValue value = FIXTURE_Value();
  RTValueSetInteger(value, NULL);
  ASSERT(value->type == INTEGER);
  ASSERT(value->primitive.integer == NULL);
  ASSERT(value->initialized == TRUE);
  AFTER_Value(value);
}

static void TEST_RTValueSetList_Valid(void) {
  RTValue value = FIXTURE_Value();
  RTValueSetList(value, NULL);
  ASSERT(value->type == LIST);
  ASSERT(value->primitive.list == NULL);
  ASSERT(value->initialized == TRUE);
  AFTER_Value(value);
}

static void TEST_RTValueSetMap_Valid(void) {
  RTValue value = FIXTURE_Value();
  RTValueSetMap(value, NULL);
  ASSERT(value->type == MAP);
  ASSERT(value->primitive.map == NULL);
  ASSERT(value->initialized == TRUE);
  AFTER_Value(value);
}

static void TEST_RTValueSetString_Valid(void) {
  RTValue value = FIXTURE_Value();
  RTValueSetString(value, NULL);
  ASSERT(value->type == STRING);
  ASSERT(value->primitive.string == NULL);
  ASSERT(value->initialized == TRUE);
  AFTER_Value(value);
}

static void TEST_RTValueGetPrimitive_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTValue value = FIXTURE_ValueInitialized(id);
  ASSERT(RTValueGetPrimitive(value).id == id);
  AFTER_Value(value);
}

static void TEST_RTValueHash_IdentifierPrimitive(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTValue value = FIXTURE_ValueInitialized(id);
  ASSERT(RTValueHash(value) == RTIdentifierHash(id));
  AFTER_Value(value);
}

static void TEST_RTValueEqual_Identity(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTValue value = FIXTURE_ValueInitialized(id);
  ASSERT(RTValueEqual(value, value) == TRUE);
  AFTER_Value(value);
}

int main(void) {
  TEST_RTValueCreate_Valid();
  TEST_RTValueDealloc_NotInitialized();
  TEST_RTValueDealloc_Initialized();
  TEST_RTValueSetIdentifier_Valid();
  TEST_RTValueSetInteger_Valid();
  TEST_RTValueSetList_Valid();
  TEST_RTValueSetMap_Valid();
  TEST_RTValueSetString_Valid();
  TEST_RTValueGetPrimitive_Valid();
  TEST_RTValueHash_IdentifierPrimitive();
  TEST_RTValueEqual_Identity();
}

#endif
