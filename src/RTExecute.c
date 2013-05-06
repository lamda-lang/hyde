#include "RTExecute.h"

typedef enum {
  RTOpcodeCreateBooleanFalse = 0,
  RTOpcodeCreateBooleanTrue = 1,
  RTOpcodeCreateIdentifier = 2,
  RTOpcodeCreateInteger = 3,
  RTOpcodeCreateLambda = 4,
  RTOpcodeCreateList = 5,
  RTOpcodeCreateMap = 6,
  RTOpcodeCreateNil = 7,
  RTOpcodeCreateString = 8,
  RTOpcodeApplyArgs = 9
} RTOpcode;

static inline RTBool CreateBoolean(RTByte **code, RTValue *reg, RTPool pool, RTBool bool) {
  RTBoolean boolean = RTBooleanCreate(bool);
  if (boolean == NULL) {
    return FALSE;
  }
  RTValue value = RTBooleanValueBridge(boolean);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateIdentifier(RTByte **code, RTValue *reg, RTPool pool) {
  RTIdentifier id = RTIdentifierDecode(code);
  if (id == NULL) {
    return FALSE;
  }
  RTValue value = RTIdentifierValueBridge(id);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateInteger(RTByte **code, RTValue *reg, RTPool pool) {
  RTInteger integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return FALSE;
  }
  RTValue value = RTIntegerValueBridge(integer);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
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
  RTValue value = RTLambdaValueBridge(lambda);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
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
  RTValue value = RTListValueBridge(list);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
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
  RTValue value = RTMapValueBridge(map);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateNil(RTByte **code, RTValue *reg, RTPool pool) {
  RTNil nil = RTNilCreate();
  if (nil == NULL) {
    return FALSE;
  }
  RTValue value = RTNilValueBridge(nil);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateString(RTByte **code, RTValue *reg, RTPool pool) {
  RTString string = RTStringDecode(code);
  if (string == NULL) {
    return FALSE;
  }
  RTValue value = RTStringValueBridge(string);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool ApplyArgs(RTByte **code, RTValue *reg, RTPool pool) {
  RTValue target = reg[RTDecodeVBRInteger32Bit(code)];
  RTLambda lambda = RTValueLambdaBridge(target);
  if (lambda == NULL) {
    return FALSE;
  }
  RTInteger8Bit count = RTDecodeInteger8Bit(code);
  RTValue arg[count];
  for (RTInteger8Bit index = 0; index < count; index += 1) {
    arg[index] = reg[RTDecodeVBRInteger32Bit(code)];
  }
  RTValue result = RTLambdaExecute(lambda, arg, count);
  if (result == NULL) {
    return FALSE;
  }
  reg[RTDecodeVBRInteger32Bit(code)] = result;
  return RTPoolAddValue(pool, result);
}

static inline RTBool ExecuteInstruction(RTByte **code, RTValue *reg, RTPool pool) {
  RTOpcode opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case RTOpcodeCreateIdentifier:
    return CreateIdentifier(code, reg, pool);
  case RTOpcodeCreateInteger:
    return CreateInteger(code, reg, pool);
  case RTOpcodeCreateLambda:
    return CreateLambda(code, reg, pool);
  case RTOpcodeCreateList:
    return CreateList(code, reg, pool);
  case RTOpcodeCreateMap:
    return CreateMap(code, reg, pool);
  case RTOpcodeCreateNil:
    return CreateNil(code, reg, pool);
  case RTOpcodeCreateString:
    return CreateString(code, reg, pool);
  case RTOpcodeCreateBooleanFalse:
    return CreateBoolean(code, reg, pool, FALSE);
  case RTOpcodeCreateBooleanTrue:
    return CreateBoolean(code, reg, pool, TRUE);
  case RTOpcodeApplyArgs:
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
