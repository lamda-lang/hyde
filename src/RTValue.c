#include "RTValue.h"

enum {
  TYPE_BOOL = 0,
  TYPE_IDENTIFIER = 1,
  TYPE_INTEGER = 2,
  TYPE_LAMBDA = 3,
  TYPE_LIST = 4,
  TYPE_MAP = 5,
  TYPE_NIL = 6,
  TYPE_STRING = 7
};

enum {
  FLAG_BOOL= 1 << 0,
  FLAG_MARK= 1 << 1,
  FLAG_PRIMITIVE= 1 << 2
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
  SetFlag(value, FLAG_MARK, FALSE);
  SetFlag(value, FLAG_PRIMITIVE, FALSE);
  return value;
}

void RTValueDealloc(RTValue value) {
  if (GetFlag(value, FLAG_PRIMITIVE) == TRUE) {
    switch (value->type) {
    case TYPE_IDENTIFIER:
      RTIdentifierDealloc(value->primitive.id);
      break;
    case TYPE_INTEGER:
      RTIntegerDealloc(value->primitive.integer);
      break;
    case TYPE_LAMBDA:
      RTLambdaDealloc(value->primitive.lambda);
      break;
    case TYPE_LIST:
      RTListDealloc(value->primitive.list);
      break;
    case TYPE_MAP:
      RTMapDealloc(value->primitive.map);
      break;
    case TYPE_STRING:
      RTStringDealloc(value->primitive.string);
      break;
    }
  }
  RTMemoryDealloc(value);
}

void RTValueSetNil(RTValue value) {
  value->type = TYPE_NIL;
  SetFlag(value, FLAG_PRIMITIVE, FALSE);
}

void RTValueSetBool(RTValue value, RTBool boolean) {
  value->type = TYPE_BOOL;
  SetFlag(value, FLAG_BOOL, boolean);
  SetFlag(value, FLAG_PRIMITIVE, FALSE);
}

void RTValueSetIdentifier(RTValue value, RTIdentifier id) {
  value->primitive.id = id;
  value->type = TYPE_IDENTIFIER;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

void RTValueSetInteger(RTValue value, RTInteger integer) {
  value->primitive.integer = integer;
  value->type = TYPE_INTEGER;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

void RTValueSetLambda(RTValue value, RTLambda lambda) {
  value->primitive.lambda = lambda;
  value->type = TYPE_LAMBDA;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

void RTValueSetList(RTValue value, RTList list) {
  value->primitive.list = list;
  value->type = TYPE_LIST;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

void RTValueSetMap(RTValue value, RTMap map) {
  value->primitive.map = map;
  value->type = TYPE_MAP;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

void RTValueSetString(RTValue value, RTString string) {
  value->primitive.string = string;
  value->type = TYPE_STRING;
  SetFlag(value, FLAG_PRIMITIVE, TRUE);
}

RTPrimitive RTValueGetPrimitive(RTValue value) {
  return value->primitive;
}

RTInteger64Bit RTValueHash(RTValue value) {
  switch (value->type) {
  case TYPE_IDENTIFIER:
    return RTIdentifierHash(value->primitive.id);
  case TYPE_INTEGER:
    return RTIntegerHash(value->primitive.integer);
  case TYPE_LAMBDA:
    return RTLambdaHash(value->primitive.lambda);
  case TYPE_LIST:
    return RTListHash(value->primitive.list);
  case TYPE_MAP:
    return RTMapHash(value->primitive.map);
  case TYPE_NIL:
    return 0;
  case TYPE_STRING:
    return RTStringHash(value->primitive.string);
  }
}

RTBool RTValueEqual(RTValue value, RTValue other) {
  if (value->type != other->type) {
    return FALSE;
  }
  switch (value->type) {
  case TYPE_IDENTIFIER:
    return RTIdentifierEqual(value->primitive.id, other->primitive.id);
  case TYPE_INTEGER:
    return RTIntegerEqual(value->primitive.integer, other->primitive.integer);
  case TYPE_LAMBDA:
    return RTLambdaEqual(value->primitive.lambda, other->primitive.lambda);
  case TYPE_LIST:
    return RTListEqual(value->primitive.list, other->primitive.list);
  case TYPE_MAP:
    return RTMapEqual(value->primitive.map, other->primitive.map);
  case TYPE_NIL:
    return TRUE;
  case TYPE_STRING:
    return RTStringEqual(value->primitive.string, other->primitive.string);
  }
}

void RTValueMark(RTValue value) {
  if (GetFlag(value, FLAG_MARK) == TRUE) {
    return;
  }
  SetFlag(value, FLAG_MARK, TRUE);
  switch (value->type) {
  case TYPE_LAMBDA:
    RTLambdaEnumerateContext(value->primitive.lambda, RTValueMark);
  case TYPE_LIST:
    RTListEnumerateValues(value->primitive.list, RTValueMark);
  case TYPE_MAP:
    RTMapEnumerateKeys(value->primitive.map, RTValueMark);
    RTMapEnumerateValues(value->primitive.map, RTValueMark);
  }
}

RTBool RTValueResetMark(RTValue value) {
  RTBool mark = GetFlag(value, FLAG_MARK);
  SetFlag(value, FLAG_MARK, FALSE);
  return mark;
}
