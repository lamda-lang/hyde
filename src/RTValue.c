#include "RTValue.h"

typedef enum {
  IDENTIFIER = 0,
  INTEGER = 1,
  LIST = 2,
  MODULE = 3,
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
    case MODULE:
      RTModuleDealloc(value->primitive.module);
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

void RTValueSetModule(RTValue value, RTModule module) {
  value->primitive.module = module;
  value->type = MODULE;
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
  case MODULE:
    return RTModuleHash(value->primitive.module);
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
  case MODULE:
    return RTModuleEqual(value->primitive.module, other->primitive.module);
  case STRING:
    return RTStringEqual(value->primitive.string, other->primitive.string);
  }
}

#ifdef RT_VALUE_TEST

int main(void) {

}

#endif
