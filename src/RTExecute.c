#include "RTExecute.h"

enum {
  CREATE_BOOLEAN_FALSE = 0,
  CREATE_BOOLEAN_TRUE = 1,
  CREATE_IDENTIFIER = 2,
  CREATE_INTEGER = 3,
  CREATE_LAMBDA = 4,
  CREATE_LIST = 5,
  CREATE_MAP = 6,
  CREATE_NIL = 7,
  CREATE_STRING = 8,
  APPLY_ARG = 9,
  FETCH_LAMBDA = 10,
  FETCH_LIST = 11,
  FETCH_MAP = 12
};

static inline RTBool CreateBoolean(RTByte **code, RTValue *reg, RTPool pool, RTBool flag) {
  RTBoolean boolean = RTBooleanCreate(flag);
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
  RTLambda lambda = RTLambdaDecode(code);
  if (lambda == NULL) {
    return FALSE;
  }
  RTValue value = RTLambdaValueBridge(lambda);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateList(RTByte **code, RTValue *reg, RTPool pool) {
  RTList list = RTListDecode(code);
  if (list == NULL) {
    return FALSE;
  }
  RTValue value = RTListValueBridge(list);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return RTPoolAddValue(pool, value);
}

static inline RTBool CreateMap(RTByte **code, RTValue *reg, RTPool pool) {
  RTMap map = RTMapDecode(code);
  if (map == NULL) {
    return FALSE;
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

static inline RTBool ApplyArg(RTByte **code, RTValue *reg, RTPool pool) {
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

static inline RTBool FetchLambda(RTByte **code, RTValue *reg) {
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTLambda lambda = RTValueLambdaBridge(value);
  if (lambda == NULL) {
    return FALSE;
  }
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue context = reg[RTDecodeVBRInteger32Bit(code)];
    RTLambdaSetContextValueAtIndex(lambda, context, index);
  }
  return TRUE;
}

static inline RTBool FetchList(RTByte **code, RTValue *reg) {
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTList list = RTValueListBridge(value);
  if (list == NULL) {
    return FALSE;
  }
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue element = reg[RTDecodeVBRInteger32Bit(code)];
    RTListSetValueAtIndex(list, element, index);
  }
  return TRUE;
}

static inline RTBool FetchMap(RTByte **code, RTValue *reg) {
  RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
  RTMap map = RTValueMapBridge(value);
  if (map == NULL) {
    return FALSE;
  }
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue key = reg[RTDecodeVBRInteger32Bit(code)];
    RTValue value = reg[RTDecodeVBRInteger32Bit(code)];
    RTMapSetValueForKey(map, value, key);
  }
  return TRUE;
}

static inline RTBool ExecuteInstruction(RTByte **code, RTValue *reg, RTPool pool) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case CREATE_BOOLEAN_FALSE:
    return CreateBoolean(code, reg, pool, FALSE);
  case CREATE_BOOLEAN_TRUE:
    return CreateBoolean(code, reg, pool, TRUE);
  case CREATE_IDENTIFIER:
    return CreateIdentifier(code, reg, pool);
  case CREATE_INTEGER:
    return CreateInteger(code, reg, pool);
  case CREATE_LAMBDA:
    return CreateLambda(code, reg, pool);
  case CREATE_LIST:
    return CreateList(code, reg, pool);
  case CREATE_MAP:
    return CreateMap(code, reg, pool);
  case CREATE_NIL:
    return CreateNil(code, reg, pool);
  case CREATE_STRING:
    return CreateString(code, reg, pool);
  case APPLY_ARG:
    return ApplyArg(code, reg, pool);
  case FETCH_LAMBDA:
    return FetchLambda(code, reg);
  case FETCH_LIST:
    return FetchList(code, reg);
  case FETCH_MAP:
    return FetchMap(code, reg);
  }
}

RTBool RTExecuteCode(RTByte *code, RTInteger32Bit count, RTValue *reg, RTPool pool) {
  while (count > 0) {
    if (!ExecuteInstruction(&code, reg, pool)) {
      return FALSE;
    }
    count -= 1;
  }
  return TRUE;
}
