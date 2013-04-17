#include "RTValue.h"

typedef enum {
  IDENTIFIER = 0,
  INTEGER = 1,
  LAMBDA = 2,
  LIST = 3,
  MAP = 4,
  STRING = 5
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
    case LAMBDA:
      RTLambdaDealloc(value->primitive.lambda);
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

void RTValueSetLambda(RTValue value, RTLambda lambda) {
  value->primitive.lambda = lambda;
  value->type = LAMBDA;
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
  case LAMBDA:
    return RTLambdaHash(value->primitive.lambda);
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
  case LAMBDA:
    return RTLambdaEqual(value->primitive.lambda, other->primitive.lambda);
  case LIST:
    return RTListEqual(value->primitive.list, other->primitive.list);
  case MAP:
    return RTMapEqual(value->primitive.map, other->primitive.map);
  case STRING:
    return RTStringEqual(value->primitive.string, other->primitive.string);
  }
}
