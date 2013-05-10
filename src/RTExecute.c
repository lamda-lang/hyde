#include "RTExecute.h"

static inline RTError AddToPool(RTPool *pool, RTValue *value) {
  return RTPoolAddValue(pool, value) == NULL ? RTErrorOutOfMemory : RTErrorNone;
}

static inline RTError CreateBoolean(RTByte **code, RTValue **reg, RTPool *pool, bool flag) {
  RTBoolean *boolean = RTBooleanCreate(flag);
  if (boolean == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTBooleanValueBridge(boolean);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateIdentifier(RTByte **code, RTValue **reg, RTPool *pool) {
  RTIdentifier *id = RTIdentifierDecode(code);
  if (id == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTIdentifierValueBridge(id);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateInteger(RTByte **code, RTValue **reg, RTPool *pool) {
  RTInteger *integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTIntegerValueBridge(integer);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateLambda(RTByte **code, RTValue **reg, RTPool *pool) {
  RTLambda *lambda = RTLambdaDecode(code);
  if (lambda == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTLambdaValueBridge(lambda);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateList(RTByte **code, RTValue **reg, RTPool *pool) {
  RTList *list = RTListDecode(code);
  if (list == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTListValueBridge(list);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateMap(RTByte **code, RTValue **reg, RTPool *pool) {
  RTMap *map = RTMapDecode(code);
  if (map == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTMapValueBridge(map);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateNil(RTByte **code, RTValue **reg, RTPool *pool) {
  RTNil *nil = RTNilCreate();
  if (nil == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTNilValueBridge(nil);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError CreateString(RTByte **code, RTValue **reg, RTPool *pool) {
  RTString *string = RTStringDecode(code);
  if (string == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTStringValueBridge(string);
  reg[RTDecodeVBRInteger32Bit(code)] = value;
  return AddToPool(pool, value);
}

static inline RTError ApplyArg(RTByte **code, RTValue **reg, RTPool *pool) {
  RTValue *target = reg[RTDecodeVBRInteger32Bit(code)];
  if (RTValueType(target) != RTTypeLambda) {
    return RTErrorInvalidType;
  }
  RTLambda *lambda = RTValueLambdaBridge(target);
  RTInteger32Bit registerCount = RTLambdaRegisterCount(lambda);
  RTSize size = sizeof(RTValue *) * registerCount;
  RTValue **frame = RTMemoryAlloc(size);
  RTInteger8Bit arity = RTDecodeInteger8Bit(code);
  for (RTInteger8Bit index = 0; index < arity; index += 1) {
    frame[index + 1] = reg[RTDecodeVBRInteger32Bit(code)];
  }
  RTError error = RTLambdaExecute(lambda, frame, arity, pool);
  if (error != RTErrorNone) {
    return error;
  }
  reg[RTDecodeVBRInteger32Bit(code)] = frame[0];
  RTMemoryDealloc(frame);
  return RTErrorNone;
}

static inline RTError FetchLambda(RTByte **code, RTValue **reg) {
  RTValue *value = reg[RTDecodeVBRInteger32Bit(code)];
  if (RTValueType(value) != RTTypeLambda) {
    return RTErrorInvalidType;
  }
  RTLambda *lambda = RTValueLambdaBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue *context = reg[RTDecodeVBRInteger32Bit(code)];
    RTLambdaSetContextValueAtIndex(lambda, context, index);
  }
  return RTErrorNone;
}

static inline RTError FetchList(RTByte **code, RTValue **reg) {
  RTValue *value = reg[RTDecodeVBRInteger32Bit(code)];
  if (RTValueType(value) != RTTypeList) {
    return RTErrorInvalidType;
  }
  RTList *list = RTValueListBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue *element = reg[RTDecodeVBRInteger32Bit(code)];
    RTListSetValueAtIndex(list, element, index);
  }
  return RTErrorNone;
}

static inline RTError FetchMap(RTByte **code, RTValue **reg) {
  RTValue *value = reg[RTDecodeVBRInteger32Bit(code)];
  if (RTValueType(value) != RTTypeMap) {
    return RTErrorInvalidType;
  }
  RTMap *map = RTValueMapBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValue *key = reg[RTDecodeVBRInteger32Bit(code)];
    RTValue *value = reg[RTDecodeVBRInteger32Bit(code)];
    RTMapSetValueForKey(map, value, key);
  }
  return RTErrorNone;
}

static inline RTError ExecuteInstruction(RTByte **code, RTValue **reg, RTPool *pool) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case 0:
    return CreateBoolean(code, reg, pool, false);
  case 1:
    return CreateBoolean(code, reg, pool, true);
  case 2:
    return CreateIdentifier(code, reg, pool);
  case 3:
    return CreateInteger(code, reg, pool);
  case 4:
    return CreateLambda(code, reg, pool);
  case 5:
    return CreateList(code, reg, pool);
  case 6:
    return CreateMap(code, reg, pool);
  case 7:
    return CreateNil(code, reg, pool);
  case 8:
    return CreateString(code, reg, pool);
  case 9:
    return ApplyArg(code, reg, pool);
  case 10:
    return FetchLambda(code, reg);
  case 11:
    return FetchList(code, reg);
  case 12:
    return FetchMap(code, reg);
  default:
    return RTErrorInvalidOpcode;
  }
}

RTError RTExecuteCode(RTByte *code, RTInteger32Bit count, RTValue **reg, RTPool *pool) {
  while (count > 0) {
    RTError error = ExecuteInstruction(&code, reg, pool);
    if (error != RTErrorNone) {
      return error;
    }
    count -= 1;
  }
  return RTErrorNone;
}
