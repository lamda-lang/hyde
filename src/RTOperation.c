#include "RTOperation.h"

enum {
  CREATE_IDENTIFIER = 0,
  CREATE_INTEGER = 1,
  CREATE_LAMBDA = 2,
  CREATE_LIST = 3,
  CREATE_MAP = 4,
  CREATE_NIL = 5,
  CREATE_STRING = 6
};

static inline RTBool CreateIdentifier(RTByte **code, RTValue *reg) {
  RTIdentifier id = RTIdentifierDecode(code);
  if (id == NULL) {
    return FALSE;
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetIdentifier(value, id);
  return TRUE;
}

static inline RTBool CreateInteger(RTByte **code, RTValue *reg) {
  RTInteger integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return FALSE;
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetInteger(value, integer);
  return TRUE;
}

static inline RTBool CreateLambda(RTByte **code, RTValue *reg) {
  RTInteger8Bit arity = RTDecodeInteger8Bit(code);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(code);
  RTLambda lambda = RTLambdaCreate(*code, length, arity, count);
  if (lambda == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
    RTLambdaSetContextValueAtIndex(lambda, value, index);
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetLambda(value, lambda);
  return TRUE;
}

static inline RTBool CreateList(RTByte **code, RTValue *reg) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(code);
  RTList list = RTListCreate(length);
  if (list == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
    RTListSetValueAtIndex(list, value, index);
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetList(value, list);
  return TRUE;
}

static inline RTBool CreateMap(RTByte **code, RTValue *reg) {
  RTInteger32Bit capacity = RTDecodeVBRInteger32Bit(code);
  RTMap map = RTMapCreate(capacity);
  if (map == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < capacity; index += 1) {
    RTValue key = reg[RTDecodeVBRInteger32Bit(code)];
    RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
    RTMapSetValueForKey(map, value, key);
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetMap(value, map);
  return TRUE;
}

static inline RTBool CreateNil(RTByte **code, RTValue *reg) {
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetNil(value);
  return TRUE;
}

static inline RTBool CreateString(RTByte **code, RTValue *reg) {
  RTString string = RTStringDecode(code);
  if (string == NULL) {
    return FALSE;
  }
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTValueSetString(value, string);
  return TRUE;
}

RTBool RTOperationExecute(RTByte **code, RTValue *reg) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case CREATE_IDENTIFIER:
    return CreateIdentifier(code, reg);
  case CREATE_INTEGER:
    return CreateInteger(code, reg);
  case CREATE_LAMBDA:
    return CreateLambda(code, reg);
  case CREATE_LIST:
    return CreateList(code, reg);
  case CREATE_MAP:
    return CreateMap(code, reg);
  case CREATE_NIL:
    return CreateNil(code, reg);
  case CREATE_STRING:
    return CreateString(code, reg);
  }
}
