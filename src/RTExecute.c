#include "RTExecute.h"

typedef RTStatus RTInstruction(RTByte **code, RTStack *stack);

static inline RTStatus CreateBooleanTrue(RTByte **code, RTStack *stack) {
  RTBoolean *boolean = RTBooleanCreate(true);
  if (boolean == NULL) {
    goto error;
  }
  RTValue *value = RTBooleanValueBridge(boolean);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateBooleanFalse(RTByte **code, RTStack *stack) {
  RTBoolean *boolean = RTBooleanCreate(false);
  if (boolean == NULL) {
    goto error;
  }
  RTValue *value = RTBooleanValueBridge(boolean);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateIdentifier(RTByte **code, RTStack *stack) {
  RTIdentifier *id = RTIdentifierDecode(code);
  if (id == NULL) {
    goto error;
  }
  RTValue *value = RTIdentifierValueBridge(id);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateInteger(RTByte **code, RTStack *stack) {
  RTInteger *integer = RTIntegerDecode(code);
  if (integer == NULL) {
    goto error;
  }
  RTValue *value = RTIntegerValueBridge(integer);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateLambda(RTByte **code, RTStack *stack) {
  RTLambda *lambda = RTLambdaDecode(code);
  if (lambda == NULL) {
    goto error;
  }
  RTValue *value = RTLambdaValueBridge(lambda);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateList(RTByte **code, RTStack *stack) {
  RTList *list = RTListDecode(code);
  if (list == NULL) {
    goto error;
  }
  RTValue *value = RTListValueBridge(list);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateMap(RTByte **code, RTStack *stack) {
  RTMap *map = RTMapDecode(code);
  if (map == NULL) {
    goto error;
  }
  RTValue *value = RTMapValueBridge(map);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateNil(RTByte **code, RTStack *stack) {
  RTNil *nil = RTNilCreate();
  if (nil == NULL) {
    goto error;
  }
  RTValue *value = RTNilValueBridge(nil);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus CreateString(RTByte **code, RTStack *stack) {
  RTString *string = RTStringDecode(code);
  if (string == NULL) {
    goto error;
  }
  RTValue *value = RTStringValueBridge(string);
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, value, index);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus ApplyArg(RTByte **code, RTStack *stack) {
  RTInteger32Bit targetIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *target = RTStackGetValueFromTopFrame(stack, targetIndex);
  if (RTValueType(target) != RTTypeLambda) {
    goto error;
  }
  RTLambda *lambda = RTValueLambdaBridge(target);
  RTInteger32Bit frameLength = RTLambdaRegisterCount(lambda);
  if (!RTStackBuildNextFrame(stack, frameLength)) {
    goto error;
  }
  RTInteger8Bit argCount = RTDecodeInteger8Bit(code);
  for (RTInteger8Bit index = 0; index < argCount; index += 1) {
    RTInteger32Bit argIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *arg = RTStackGetValueFromTopFrame(stack, argIndex);
    RTStackSetArgInNextFrame(stack, arg, index);
  }
  RTStackPushNextFrame(stack);
  if (!RTLambdaExecute(lambda, stack, argCount)) {
    goto errorExecute;
  }
  RTValue *result = RTStackReturnFromTopFrame(stack);
  RTInteger32Bit resultIndex = RTDecodeVBRInteger32Bit(code);
  RTStackSetValueInTopFrame(stack, result, resultIndex);
  return RTStatusSuccess;

errorExecute:
  RTStackCleanTopFrame(stack);
error:
  return RTStatusFailure;
}

static inline RTStatus FetchLambda(RTByte **code, RTStack *stack) {
  RTInteger32Bit lambdaIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, lambdaIndex);
  if (RTValueType(value) != RTTypeLambda) {
    goto error;
  }
  RTLambda *lambda = RTValueLambdaBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTInteger32Bit contextIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *context = RTStackGetValueFromTopFrame(stack, contextIndex);
    RTLambdaSetContextValueAtIndex(lambda, context, index);
  }
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus FetchList(RTByte **code, RTStack *stack) {
  RTInteger32Bit listIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, listIndex);
  if (RTValueType(value) != RTTypeList) {
    goto error;
  }
  RTList *list = RTValueListBridge(value);
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(code);
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTInteger32Bit elementIndex = RTDecodeVBRInteger32Bit(code);
    RTValue *element = RTStackGetValueFromTopFrame(stack, elementIndex);
    RTListSetValueAtIndex(list, element, index);
  }
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static inline RTStatus FetchMap(RTByte **code, RTStack *stack) {
  RTInteger32Bit mapIndex = RTDecodeVBRInteger32Bit(code);
  RTValue *value = RTStackGetValueFromTopFrame(stack, mapIndex);
  if (RTValueType(value) != RTTypeMap) {
    goto error;
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
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}

static RTInstruction *instruction[] = {
  [0] = CreateBooleanTrue,
  [1] = CreateBooleanFalse,
  [2] = CreateIdentifier,
  [3] = CreateInteger,
  [4] = CreateLambda,
  [5] = CreateList,
  [6] = CreateMap,
  [7] = CreateNil,
  [8] = CreateString,
  [9] = ApplyArg,
  [10] = FetchLambda,
  [11] = FetchList,
  [12] = FetchMap
};

RTStatus RTExecuteCode(RTByte *code, RTInteger32Bit count, RTStack *stack) {
  while (count > 0) {
    RTInteger8Bit opcode = RTDecodeInteger8Bit(&code);
    if (!instruction[opcode](&code, stack)) {
      goto error;
    }
    count -= 1;
  }
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}
