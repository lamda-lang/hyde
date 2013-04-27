#include "RTValue.h"

enum {
  IDENTIFIER = 0,
  INTEGER = 1,
  LAMBDA = 2,
  LIST = 3,
  MAP = 4,
  STRING = 5
};

enum {
  MARK = 1 << 0,
  INIT = 1 << 1
};

struct RTValue {
  RTPrimitive primitive;
  RTInteger8Bit flag;
  RTInteger8Bit type;
};

static inline void SetFlag(RTValue value, RTInteger8Bit flag, RTBool boolean) {
  if (boolean == TRUE) {
    value->flag |= flag;
  } else {
    value->flag &= ~flag;
  }
}

static inline RTBool GetFlag(RTValue value, RTInteger8Bit flag) {
  return (value->flag & flag) != 0;
}

RTValue RTValueCreate() {
  RTValue value = RTMemoryAlloc(sizeof(struct RTValue));
  if (value == NULL) {
    return NULL;
  }
  SetFlag(value, INIT, FALSE);
  return value;
}

void RTValueDealloc(RTValue value) {
  if (GetFlag(value, INIT) == TRUE) {
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
  SetFlag(value, INIT, TRUE);
}

void RTValueSetInteger(RTValue value, RTInteger integer) {
  value->primitive.integer = integer;
  value->type = INTEGER;
  SetFlag(value, INIT, TRUE);
}

void RTValueSetLambda(RTValue value, RTLambda lambda) {
  value->primitive.lambda = lambda;
  value->type = LAMBDA;
  SetFlag(value, INIT, TRUE);
}

void RTValueSetList(RTValue value, RTList list) {
  value->primitive.list = list;
  value->type = LIST;
  SetFlag(value, INIT, TRUE);
}

void RTValueSetMap(RTValue value, RTMap map) {
  value->primitive.map = map;
  value->type = MAP;
  SetFlag(value, INIT, TRUE);
}

void RTValueSetString(RTValue value, RTString string) {
  value->primitive.string = string;
  value->type = STRING;
  SetFlag(value, INIT, TRUE);
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

void RTValueMark(RTValue value) {
  if (GetFlag(value, MARK) == TRUE) {
    return;
  }
  SetFlag(value, MARK, TRUE);
  switch (value->type) {
  case LAMBDA:
    RTLambdaEnumerateContext(value->primitive.lambda, RTValueMark);
  case LIST:
    RTListEnumerateValues(value->primitive.list, RTValueMark);
  case MAP:
    RTMapEnumerateKeys(value->primitive.map, RTValueMark);
    RTMapEnumerateValues(value->primitive.map, RTValueMark);
  }
}

RTBool RTValueResetMark(RTValue value) {
  RTBool mark = GetFlag(value, MARK);
  SetFlag(value, MARK, FALSE);
  return mark;
}
