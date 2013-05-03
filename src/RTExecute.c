#include "RTExecute.h"

typedef enum {
  OPCODE_CREATE_IDENTIFIER = 0,
  OPCODE_CREATE_INTEGER = 1,
  OPCODE_CREATE_LAMBDA = 2,
  OPCODE_CREATE_LIST = 3,
  OPCODE_CREATE_MAP = 4,
  OPCODE_CREATE_NIL = 5,
  OPCODE_CREATE_STRING = 6,
  OPCODE_CREATE_BOOL_TRUE = 7,
  OPCODE_CREATE_BOOL_FALSE = 8,
  OPCODE_APPLY_ARGS = 9
} RTOpcode;

static inline void SetValue(RTByte **code, RTValue *reg, RTValue value) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  reg[index] = value;
}

static inline RTBool CreateIdentifier(RTByte **code, RTValue *reg) {
  RTIdentifier id = RTIdentifierDecode(code);
  if (id == NULL) {
    return FALSE;
  }
  RTValue value = RTValueCreateIdentifier(id);
  if (value == NULL) {
    RTIdentifierDealloc(id);
    return FALSE;
  }
  SetValue(code, reg, value);
  return TRUE;
}

static inline RTBool CreateInteger(RTByte **code, RTValue *reg) {
  RTInteger integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return FALSE;
  }
  RTValue value = RTValueCreateInteger(integer);
  if (value == NULL) {
    RTIntegerDealloc(integer);
    return FALSE;
  }
  SetValue(code, reg, value);
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
  RTValue value = RTValueCreateLambda(lambda);
  if (value == NULL) {
    RTLambdaDealloc(lambda);
    return FALSE;
  }
  SetValue(code, reg, value);
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
  RTValue value = RTValueCreateList(list);
  if (value == NULL) {
    RTListDealloc(list);
    return FALSE;
  }
  SetValue(code, reg, value);
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
  RTValue value = RTValueCreateMap(map);
  if (value == NULL) {
    RTMapDealloc(map);
    return FALSE;
  }
  SetValue(code, reg, value);
  return TRUE;
}

static inline RTBool CreateNil(RTByte **code, RTValue *reg) {
  RTValue value = RTValueCreateNil();
  if (value == NULL) {
    return FALSE;
  }
  SetValue(code, reg, value);
  return TRUE;
}

static inline RTBool CreateString(RTByte **code, RTValue *reg) {
  RTString string = RTStringDecode(code);
  if (string == NULL) {
    return FALSE;
  }
  RTValue value = RTValueCreateString(string);
  if (value == NULL) {
    RTStringDealloc(string);
    return FALSE;
  }
  SetValue(code, reg, value);
  return TRUE;
}

static inline RTBool CreateBool(RTByte **code, RTValue *reg, RTBool boolean) {
  RTValue value = RTValueCreateBool(boolean);
  if (value == NULL) {
    return FALSE;
  }
  SetValue(code, reg, value);
  return TRUE;
}

static inline RTBool ApplyArgs(RTByte **code, RTValue *reg) {
  return TRUE;
}

static inline RTBool ExecuteInstruction(RTByte **code, RTValue *reg, RTPool pool) {
  RTOpcode opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case OPCODE_CREATE_IDENTIFIER:
    return CreateIdentifier(code, reg, pool);
  case OPCODE_CREATE_INTEGER:
    return CreateInteger(code, reg, pool);
  case OPCODE_CREATE_LAMBDA:
    return CreateLambda(code, reg, pool);
  case OPCODE_CREATE_LIST:
    return CreateList(code, reg, pool);
  case OPCODE_CREATE_MAP:
    return CreateMap(code, reg, pool);
  case OPCODE_CREATE_NIL:
    return CreateNil(code, reg, pool);
  case OPCODE_CREATE_STRING:
    return CreateString(code, reg, pool);
  case OPCODE_CREATE_BOOL_TRUE:
    return CreateBool(code, reg, pool, TRUE);
  case OPCODE_CREATE_BOOL_FALSE:
    return CreateBool(code, reg, pool, FALSE);
  case OPCODE_APPLY_ARGS:
    return ApplyArgs(code, reg, pool);
  }
}

RTBool RTExecuteCode(RTByte *code, RTInteger32Bit count, RTValue *reg, RTPool pool) {
  while (count > 0) {
    if (ExecuteInstruction(&code, reg, pool) == FALSE) {
      return FALSE;
    }
    count -= 1;
  }
  return TRUE;
}

