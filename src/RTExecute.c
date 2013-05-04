#include "RTExecute.h"

typedef enum {
  OPCODE_CREATE_IDENTIFIER = 0,
  OPCODE_CREATE_INTEGER = 1,
  OPCODE_CREATE_LAMBDA = 2,
  OPCODE_CREATE_LIST = 3,
  OPCODE_CREATE_MAP = 4,
  OPCODE_SINGLETON_NIL = 5,
  OPCODE_CREATE_STRING = 6,
  OPCODE_SINGLETON_BOOLEAN_TRUE = 7,
  OPCODE_SINGLETON_BOOLEAN_FALSE = 8,
  OPCODE_APPLY_ARGS = 9
} RTOpcode;

static inline void InsertRegister(RTByte **code, RTValue *reg, RTValue value) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  reg[index] = value;
}

static inline RTBool CreateIdentifier(RTByte **code, RTValue *reg, RTPool pool) {
  RTIdentifier id = RTIdentifierDecode(code);
  if (id == NULL) {
    return FALSE;
  }
  InsertRegister(code, reg, VALUE(id));
  return RTPoolAddValue(pool, VALUE(id));
}

static inline RTBool CreateInteger(RTByte **code, RTValue *reg, RTPool pool) {
  RTInteger integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return FALSE;
  }
  InsertRegister(code, reg, VALUE(integer));
  return RTPoolAddValue(pool, VALUE(integer));
}

static inline RTBool CreateLambda(RTByte **code, RTValue *reg, RTPool pool) {
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
  InsertRegister(code, reg, VALUE(lambda));
  return RTPoolAddValue(pool, VALUE(lambda));
}

static inline RTBool CreateList(RTByte **code, RTValue *reg, RTPool pool) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(code);
  RTList list = RTListCreate(length);
  if (list == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
    RTListSetValueAtIndex(list, value, index);
  }
  InsertRegister(code, reg, VALUE(list));
  return RTPoolAddValue(pool, VALUE(list));
}

static inline RTBool CreateMap(RTByte **code, RTValue *reg, RTPool pool) {
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
  InsertRegister(code, reg, VALUE(map));
  return RTPoolAddValue(pool, VALUE(map));
}

static inline RTBool SingletonNil(RTByte **code, RTValue *reg) {
  InsertRegister(code, reg, VALUE(RTNilSingleton));
  return TRUE;
}

static inline RTBool CreateString(RTByte **code, RTValue *reg, RTPool pool) {
  RTString string = RTStringDecode(code);
  if (string == NULL) {
    return FALSE;
  }
  InsertRegister(code, reg, VALUE(string));
  return RTPoolAddValue(pool, VALUE(string));
}

static inline RTBool SingletonBooleanTrue(RTByte **code, RTValue *reg) {
  InsertRegister(code, reg, VALUE(RTBooleanTrueSingleton));
  return TRUE;
}

static inline RTBool SingletonBooleanFalse(RTByte **code, RTValue *reg) {
  InsertRegister(code, reg, VALUE(RTBooleanFalseSingleton));
  return TRUE;
}

static inline RTBool ApplyArgs(RTByte **code, RTValue *reg, RTPool pool) {
  code = NULL;
  reg = NULL;
  pool = NULL;
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
  case OPCODE_SINGLETON_NIL:
    return SingletonNil(code, reg);
  case OPCODE_CREATE_STRING:
    return CreateString(code, reg, pool);
  case OPCODE_SINGLETON_BOOLEAN_TRUE:
    return SingletonBooleanTrue(code, reg);
  case OPCODE_SINGLETON_BOOLEAN_FALSE:
    return SingletonBooleanFalse(code, reg);
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

