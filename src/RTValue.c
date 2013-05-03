#include "RTValue.h"

typedef enum {
  FLAG_NONE = 0,
  FLAG_BOOL = 1 << 0,
  FLAG_MARK = 1 << 1,
  FLAG_PRIMITIVE = 1 << 2
} RTFlag;

struct RTValue {
  RTPrimitive primitive;
  RTFlag flag;
  RTType type;
};

static inline void SetFlag(RTValue value, RTFlag flag, RTBool boolean) {
  if (boolean == TRUE) {
    value->flag |= flag;
  } else {
    value->flag &= ~flag;
  }
}

static inline RTBool GetFlag(RTValue value, RTFlag flag) {
  return (value->flag & flag) != 0;
}

static inline void DeallocPrimitive(RTPrimitive primitive, RTType type) {
  switch (type) {
  case TYPE_IDENTIFIER:
    RTIdentifierDealloc(primitive.id);
    return;
  case TYPE_INTEGER:
    RTIntegerDealloc(primitive.integer);
    return;
  case TYPE_LAMBDA:
    RTLambdaDealloc(primitive.lambda);
    return;
  case TYPE_LIST:
    RTListDealloc(primitive.list);
    return;
  case TYPE_MAP:
    RTMapDealloc(primitive.map);
    return;
  case TYPE_STRING:
    RTStringDealloc(primitive.string);
    return;
  }
}

static inline RTValue Create(RTType type, RTFlag flag) {
  RTValue value = RTMemoryAlloc(sizeof(struct RTValue));
  if (value == NULL) {
    return NULL;
  }
  value->type = type;
  value->flag = flag;
  return value;
}

static inline RTValue CreatePrimitive(RTType type, RTFlag flag, RTPrimitive primitive) {
  RTValue value = Create(type, flag);
  if (value == NULL) {
    return NULL;
  }
  value->primitive = primitive;
  return value;
}

RTValue RTValueCreateIdentifier(RTIdentifier id) {
  RTPrimitive primitive = {.id = id};
  return CreatePrimitive(TYPE_IDENTIFIER, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateInteger(RTInteger integer) {
  RTPrimitive primitive = {.integer = integer};
  return CreatePrimitive(TYPE_INTEGER, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateLambda(RTLambda lambda) {
  RTPrimitive primitive = {.lambda = lambda};
  return CreatePrimitive(TYPE_LAMBDA, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateList(RTList list) {
  RTPrimitive primitive = {.list = list};
  return CreatePrimitive(TYPE_LIST, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateMap(RTMap map) {
  RTPrimitive primitive = {.map = map};
  return CreatePrimitive(TYPE_MAP, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateString(RTString string) {
  RTPrimitive primitive = {.string = string};
  return CreatePrimitive(TYPE_STRING, FLAG_PRIMITIVE, primitive);
}

RTValue RTValueCreateNil(void) {
  return Create(TYPE_NIL, FLAG_NONE);
}

RTValue RTValueCreateBool(RTBool boolean) {
  RTFlag flag = boolean ? FLAG_BOOL : FLAG_NONE;
  return Create(TYPE_NIL, flag);
}

void RTValueDealloc(RTValue value) {
  if (GetFlag(value, FLAG_PRIMITIVE) == TRUE) {
    DeallocPrimitive(value->primitive, value->type);
  }
  RTMemoryDealloc(value);
}

RTPrimitive RTValueGetPrimitive(RTValue value) {
  return value->primitive;
}

RTInteger64Bit RTValueHash(RTValue value) {
  switch (value->type) {
  case TYPE_BOOL:
    return GetFlag(value, FLAG_BOOL) ? 1 : 0;
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
  case TYPE_BOOL:
    return GetFlag(value, FLAG_BOOL) == GetFlag(other, FLAG_BOOL);
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
