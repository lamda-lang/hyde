#include "RTExecute.h"

static inline RTError CreateBoolean(RTByte **code, RTStack *stack, bool flag) {
  RTBoolean *boolean = RTBooleanCreate(flag);
  if (boolean == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTBooleanValueBridge(boolean);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateIdentifier(RTByte **code, RTStack *stack) {
  RTIdentifier *id = RTIdentifierDecode(code);
  if (id == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTIdentifierValueBridge(id);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateInteger(RTByte **code, RTStack *stack) {
  RTInteger *integer = RTIntegerDecode(code);
  if (integer == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTIntegerValueBridge(integer);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateLambda(RTByte **code, RTStack *stack) {
  RTLambda *lambda = RTLambdaDecode(code);
  if (lambda == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTLambdaValueBridge(lambda);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateList(RTByte **code, RTStack *stack) {
  RTList *list = RTListDecode(code);
  if (list == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTListValueBridge(list);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateMap(RTByte **code, RTStack *stack) {
  RTMap *map = RTMapDecode(code);
  if (map == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTMapValueBridge(map);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateNil(RTByte **code, RTStack *stack) {
  RTNil *nil = RTNilCreate();
  if (nil == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTNilValueBridge(nil);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError CreateString(RTByte **code, RTStack *stack) {
  RTString *string = RTStringDecode(code);
  if (string == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *value = RTStringValueBridge(string);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTErrorNone;
}

static inline RTError ApplyArg(RTByte **code, RTStack *stack) {
  RTInteger32Bit targetIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *target = RTStackGetValueFromTopFrame(stack, targetIndex);
  if (RTValueType(target) != RTTypeLambda) {
    return RTErrorInvalidType;
  }
  RTLambda *lambda = RTValueLambdaBridge(target);
  RTInteger32Bit frameLength = RTLambdaRegisterCount(lambda);
  RTError stackError = RTStackBuildNextFrame(stack, frameLength);
  if (stackError != RTErrorNone) {
    return stackError;
  }
  RTInteger8Bit argCount = RTDecodeInteger8Bit(code);
  for (RTInteger8Bit index = 0; index < argCount; index += 1) {
    RTInteger32Bit argIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *arg = RTStackGetValueFromTopFrame(stack, argIndex);
    RTStackSetArgInNextFrame(stack, arg, index);
  }
  RTStackPushNextFrame(stack);
  RTError lambdaError = RTLambdaExecute(lambda, stack, argCount);
  if (lambdaError != RTErrorNone) {
    return lambdaError;
  }
  RTValue *result = RTStackReturnFromTopFrame(stack);
  RTInteger32Bit resultIndex = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, result, resultIndex);
  return RTErrorNone;
}

static inline RTError FetchLambda(RTByte **code, RTStack *stack) {
  RTInteger32Bit lambdaIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, lambdaIndex);
  if (RTValueType(value) != RTTypeLambda) {
    return RTErrorInvalidType;
  }
  RTLambda *lambda = RTValueLambdaBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTInteger32Bit contextIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *context = RTStackGetValueFromTopFrame(stack, contextIndex);
    RTLambdaSetContextValueAtIndex(lambda, context, index);
  }
  return RTErrorNone;
}

static inline RTError FetchList(RTByte **code, RTStack *stack) {
  RTInteger32Bit listIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, listIndex);
  if (RTValueType(value) != RTTypeList) {
    return RTErrorInvalidType;
  }
  RTList *list = RTValueListBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTInteger32Bit elementIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *element = RTStackGetValueFromTopFrame(stack, elementIndex);
    RTListSetValueAtIndex(list, element, index);
  }
  return RTErrorNone;
}

static inline RTError FetchMap(RTByte **code, RTStack *stack) {
  RTInteger32Bit mapIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, mapIndex);
  if (RTValueType(value) != RTTypeMap) {
    return RTErrorInvalidType;
  }
  RTMap *map = RTValueMapBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTInteger32Bit keyIndex = RTDecodeVBRInteger32Bit(code);
    RTInteger32Bit valueIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *key = RTStackGetValueFromTopFrame(stack, keyIndex);
    RTValue *value = RTStackGetValueFromTopFrame(stack, valueIndex);
    RTMapSetValueForKey(map, value, key);
  }
  return RTErrorNone;
}

static inline RTError ExecuteInstruction(RTByte **code, RTStack *stack) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(code);
  switch (opcode) {
  case 0:
    return CreateBoolean(code, stack, false);
  case 1:
    return CreateBoolean(code, stack, true);
  case 2:
    return CreateIdentifier(code, stack);
  case 3:
    return CreateInteger(code, stack);
  case 4:
    return CreateLambda(code, stack);
  case 5:
    return CreateList(code, stack);
  case 6:
    return CreateMap(code, stack);
  case 7:
    return CreateNil(code, stack);
  case 8:
    return CreateString(code, stack);
  case 9:
    return ApplyArg(code, stack);
  case 10:
    return FetchLambda(code, stack);
  case 11:
    return FetchList(code, stack);
  case 12:
    return FetchMap(code, stack);
  default:
    return RTErrorInvalidOpcode;
  }
}

RTError RTExecuteCode(RTByte *code, RTInteger32Bit count, RTStack *stack) {
  while (count > 0) {
    RTError error = ExecuteInstruction(&code, stack);
    if (error != RTErrorNone) {
      return error;
    }
    count -= 1;
  }
  return RTErrorNone;
}
