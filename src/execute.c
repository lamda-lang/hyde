#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack);

static inline Status CreateBooleanTrue(Byte **code, Stack *stack) {
  Boolean *boolean = BooleanCreate(true);
  if (boolean == NULL) {
    goto error;
  }
  Value *value = BooleanValueBridge(boolean);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateBooleanFalse(Byte **code, Stack *stack) {
  Boolean *boolean = BooleanCreate(false);
  if (boolean == NULL) {
    goto error;
  }
  Value *value = BooleanValueBridge(boolean);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateIdentifier(Byte **code, Stack *stack) {
  Identifier *id = IdentifierDecode(code);
  if (id == NULL) {
    goto error;
  }
  Value *value = IdentifierValueBridge(id);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateInteger(Byte **code, Stack *stack) {
  Integer *integer = IntegerDecode(code);
  if (integer == NULL) {
    goto error;
  }
  Value *value = IntegerValueBridge(integer);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateLambda(Byte **code, Stack *stack) {
  Lambda *lambda = LambdaDecode(code);
  if (lambda == NULL) {
    goto error;
  }
  Value *value = LambdaValueBridge(lambda);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateList(Byte **code, Stack *stack) {
  List *list = ListDecode(code);
  if (list == NULL) {
    goto error;
  }
  Value *value = ListValueBridge(list);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateMap(Byte **code, Stack *stack) {
  Map *map = MapDecode(code);
  if (map == NULL) {
    goto error;
  }
  Value *value = MapValueBridge(map);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateNil(Byte **code, Stack *stack) {
  Nil *nil = NilCreate();
  if (nil == NULL) {
    goto error;
  }
  Value *value = NilValueBridge(nil);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateString(Byte **code, Stack *stack) {
  String *string = StringDecode(code);
  if (string == NULL) {
    goto error;
  }
  Value *value = StringValueBridge(string);
  Integer32Bit index = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, value, index);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status ApplyArg(Byte **code, Stack *stack) {
  Integer32Bit targetIndex = DecodeVBRInteger32Bit(code);
  Value *target = StackGetValueFromTopFrame(stack, targetIndex);
  if (ValueType(target) != TypeLambda) {
    goto error;
  }
  Lambda *lambda = ValueLambdaBridge(target);
  Integer32Bit frameLength = LambdaRegisterCount(lambda);
  if (!StackBuildNextFrame(stack, frameLength)) {
    goto error;
  }
  Integer8Bit argCount = DecodeInteger8Bit(code);
  for (Integer8Bit index = 0; index < argCount; index += 1) {
    Integer32Bit argIndex = DecodeVBRInteger32Bit(code);
    Value *arg = StackGetValueFromTopFrame(stack, argIndex);
    StackSetArgInNextFrame(stack, arg, index);
  }
  StackPushNextFrame(stack);
  if (!LambdaExecute(lambda, stack, argCount)) {
    goto errorExecute;
  }
  Value *result = StackReturnFromTopFrame(stack);
  Integer32Bit resultIndex = DecodeVBRInteger32Bit(code);
  StackSetValueInTopFrame(stack, result, resultIndex);
  return StatusSuccess;

errorExecute:
  StackCleanTopFrame(stack);
error:
  return StatusFailure;
}

static inline Status FetchLambda(Byte **code, Stack *stack) {
  Integer32Bit lambdaIndex = DecodeVBRInteger32Bit(code);
  Value *value = StackGetValueFromTopFrame(stack, lambdaIndex);
  if (ValueType(value) != TypeLambda) {
    goto error;
  }
  Lambda *lambda = ValueLambdaBridge(value);
  Integer32Bit count = DecodeVBRInteger32Bit(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Integer32Bit contextIndex = DecodeVBRInteger32Bit(code);
    Value *context = StackGetValueFromTopFrame(stack, contextIndex);
    LambdaSetContextValueAtIndex(lambda, context, index);
  }
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status FetchList(Byte **code, Stack *stack) {
  Integer32Bit listIndex = DecodeVBRInteger32Bit(code);
  Value *value = StackGetValueFromTopFrame(stack, listIndex);
  if (ValueType(value) != TypeList) {
    goto error;
  }
  List *list = ValueListBridge(value);
  Integer32Bit count = DecodeVBRInteger32Bit(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Integer32Bit elementIndex = DecodeVBRInteger32Bit(code);
    Value *element = StackGetValueFromTopFrame(stack, elementIndex);
    ListSetValueAtIndex(list, element, index);
  }
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status FetchMap(Byte **code, Stack *stack) {
  Integer32Bit mapIndex = DecodeVBRInteger32Bit(code);
  Value *value = StackGetValueFromTopFrame(stack, mapIndex);
  if (ValueType(value) != TypeMap) {
    goto error;
  }
  Map *map = ValueMapBridge(value);
  Integer32Bit count = DecodeVBRInteger32Bit(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Integer32Bit keyIndex = DecodeVBRInteger32Bit(code);
    Integer32Bit valueIndex = DecodeVBRInteger32Bit(code);
    Value *key = StackGetValueFromTopFrame(stack, keyIndex);
    Value *value = StackGetValueFromTopFrame(stack, valueIndex);
    MapSetValueForKey(map, value, key);
  }
  return StatusSuccess;

error:
  return StatusFailure;
}

static Instruction *instruction[] = {
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

Status ExecuteCode(Byte *code, Integer32Bit count, Stack *stack) {
  while (count > 0) {
    Integer8Bit opcode = DecodeInteger8Bit(&code);
    if (!instruction[opcode](&code, stack)) {
      goto error;
    }
    count -= 1;
  }
  return StatusSuccess;

error:
  return StatusFailure;
}
