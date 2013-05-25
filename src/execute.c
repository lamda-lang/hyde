#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack);

static inline Value *GetValue(Byte **code, Stack *stack) {
  Integer32Bit index = DecodeInteger32BitVLE(code);
  return StackGetValueFromTopFrame(stack, index);
}

static inline void SetValue(Byte **code, Stack *stack, Value *value) {
  Integer32Bit index = DecodeInteger32BitVLE(code);
  StackSetValueInTopFrame(stack, value, index);
}

static inline Status CreateBoolean(Byte **code, Stack *stack, bool truth) {
  Boolean *boolean = BooleanCreate(truth);
  if (boolean == NULL) {
    goto returnError;
  }
  Value *value = BooleanValueBridge(boolean);
  SetValue(code, stack, value);
  return StatusSuccess;

error:
  return StatusFailure;
}

static inline Status CreateBooleanTrue(Byte **code, Stack *stack) {
  return CreateBoolean(true);
}

static inline Status CreateBooleanFalse(Byte **code, Stack *stack) {
  return CreateBoolean(false);
}

static inline Status CreateIdentifier(Byte **code, Stack *stack) {
  Identifier *id = IdentifierDecode(code);
  if (id == NULL) {
    goto returnError;
  }
  Value *value = IdentifierValueBridge(id);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateInteger(Byte **code, Stack *stack) {
  Integer *integer = IntegerDecode(code);
  if (integer == NULL) {
    goto returnError;
  }
  Value *value = IntegerValueBridge(integer);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateLambda(Byte **code, Stack *stack) {
  Lambda *lambda = LambdaDecode(code);
  if (lambda == NULL) {
    goto returnError;
  }
  Value *value = LambdaValueBridge(lambda);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateList(Byte **code, Stack *stack) {
  List *list = ListDecode(code);
  if (list == NULL) {
    goto returnError;
  }
  Value *value = ListValueBridge(list);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateMap(Byte **code, Stack *stack) {
  Map *map = MapDecode(code);
  if (map == NULL) {
    goto returnError;
  }
  Value *value = MapValueBridge(map);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateNil(Byte **code, Stack *stack) {
  Nil *nil = NilCreate();
  if (nil == NULL) {
    goto returnError;
  }
  Value *value = NilValueBridge(nil);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status CreateString(Byte **code, Stack *stack) {
  String *string = StringDecode(code);
  if (string == NULL) {
    goto returnError;
  }
  Value *value = StringValueBridge(string);
  SetValue(code, stack, value);
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status ApplyArg(Byte **code, Stack *stack) {
  Value *target = GetValue(code, stack);
  if (ValueType(target) != TypeLambda) {
    ExceptionRaise(ExceptionInvalidType);
    goto returnError;
  }
  Lambda *lambda = ValueLambdaBridge(target);
  Integer32Bit frameLength = LambdaRegisterCount(lambda);
  if (StackBuildNextFrame(stack, frameLength) == StatusFailure) {
    goto returnError;
  }
  Integer8Bit argCount = DecodeInteger8Bit(code);
  for (Integer8Bit index = 0; index < argCount; index += 1) {
    Value *arg = GetValue(code, stack);
    StackSetArgInNextFrame(stack, arg, index);
  }
  StackPushNextFrame(stack);
  if (LambdaExecute(lambda, stack, argCount) == StatusFailure) {
    goto cleanupStack;
  }
  Value *result = StackReturnFromTopFrame(stack);
  SetValue(code, stack, result);
  return StatusSuccess;

cleanupStack:
  StackCleanTopFrame(stack);
returnError:
  return StatusFailure;
}

static inline Status FetchLambda(Byte **code, Stack *stack) {
  Value *target = GetValue(code, stack);
  if (ValueType(target) != TypeLambda) {
    ExceptionRaise(ExceptionInvalidType);
    goto returnError;
  }
  Lambda *lambda = ValueLambdaBridge(target);
  Integer32Bit count = DecodeInteger32BitVLE(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Value *value = GetValue(code, stack);
    LambdaSetContextValueAtIndex(lambda, value, index);
  }
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status FetchList(Byte **code, Stack *stack) {
  Value *target = GetValue(code, stack);
  if (ValueType(target) != TypeList) {
    ExceptionRaise(ExceptionInvalidType);
    goto returnError;
  }
  List *list = ValueListBridge(target);
  Integer32Bit count = DecodeVBRInteger32Bit(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Value *value = GetValue(code, stack);
    ListSetValueAtIndex(list, value, index);
  }
  return StatusSuccess;

returnError:
  return StatusFailure;
}

static inline Status FetchMap(Byte **code, Stack *stack) {
  Value *target = GetValue(code, stack);
  if (ValueType(target) != TypeMap) {
    ExceptionRaise(ExceptionInvalidType);
    goto returnError;
  }
  Map *map = ValueMapBridge(value);
  Integer32Bit count = DecodeInteger32BitVLE(code);
  for (Integer32Bit index = 0; index < count; index += 1) {
    Value *key = GetValue(code, stack);
    Value *value = GetValue(code, stack);
    MapSetValueForKey(map, value, key);
  }
  return StatusSuccess;

returnError:
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
    if (instruction[opcode](&code, stack) == StatusFailure) {
      goto returnError;
    }
    count -= 1;
  }
  return StatusSuccess;

returnError:
  return StatusFailure;
}
