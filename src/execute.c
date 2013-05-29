#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack, Exception *exception);

static inline Value *GetValue(Byte **code, Stack *stack) {
    Integer32 index = DecodeInteger32VLE(code);
    return StackGetValueFromTopFrame(stack, index);
}

static inline void SetValue(Byte **code, Stack *stack, Value *value, bool transient) {
    Integer32 index = DecodeInteger32VLE(code);
    StackSetValueInTopFrame(stack, value, index, transient);
}

static inline Status CreateBooleanTrue(Byte **code, Stack *stack, Exception *exception) {
    Boolean *boolean = BooleanTrueSingleton();
    Value *booleanValue = BooleanValueBridge(boolean);
    SetValue(code, stack, booleanValue, false);
    return StatusSuccess;
}

static inline Status CreateBooleanFalse(Byte **code, Stack *stack, Exception *exception) {
    Boolean *boolean = BooleanFalseSingleton();
    Value *booleanValue = BooleanValueBridge(boolean);
    SetValue(code, stack, booleanValue, false);
    return StatusSuccess;
}

static inline Status CreateIdentifier(Byte **code, Stack *stack, Exception *exception) {
    Identifier *id = IdentifierDecode(code, exception);
    if (id == NULL) {
        goto returnError;
    }
    Value *idValue = IdentifierValueBridge(id);
    SetValue(code, stack, idValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateInteger(Byte **code, Stack *stack, Exception *exception) {
    Integer64 value = DecodeInteger64FLE(code);
    Integer *integer = IntegerCreate(value, exception);
    if (integer == NULL) {
        goto returnError;
    }
    Value *integerValue = IntegerValueBridge(integer);
    SetValue(code, stack, integerValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateLambda(Byte **code, Stack *stack, Exception *exception) {
    Lambda *lambda = LambdaDecode(code, exception);
    if (lambda == NULL) {
        goto returnError;
    }
    Value *lambdaValue = LambdaValueBridge(lambda);
    SetValue(code, stack, lambdaValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateList(Byte **code, Stack *stack, Exception *exception) {
    List *list = ListDecode(code, exception);
    if (list == NULL) {
        goto returnError;
    }
    Value *listValue = ListValueBridge(list);
    SetValue(code, stack, listValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateMap(Byte **code, Stack *stack, Exception *exception) {
    Map *map = MapDecode(code, exception);
    if (map == NULL) {
        goto returnError;
    }
    Value *mapValue = MapValueBridge(map);
    SetValue(code, stack, mapValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateNil(Byte **code, Stack *stack, Exception *exception) {
    Value *nilValue = NilValueBridge();
    SetValue(code, stack, nilValue, false);
    return StatusSuccess;
}

static inline Status CreateString(Byte **code, Stack *stack, Exception *exception) {
    String *string = StringDecode(code, exception);
    if (string == NULL) {
        goto returnError;
    }
    Value *stringValue = StringValueBridge(string);
    SetValue(code, stack, stringValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status ApplyArg(Byte **code, Stack *stack, Exception *exception) {
    Value *target = GetValue(code, stack);
    if (ValueType(target) != TypeLambda) {
        ExceptionRaise(exception, ErrorInvalidType);
        goto returnError;
    }
    Lambda *lambda = ValueLambdaBridge(target);
    Integer32 frameLength = LambdaRegisterCount(lambda);
    if (StackBuildNextFrame(stack, frameLength, exception) == StatusFailure) {
        goto returnError;
    }
    Integer8 argCount = DecodeInteger8FLE(code);
    for (Integer8 index = 0; index < argCount; index += 1) {
        Value *arg = GetValue(code, stack);
        StackSetArgInNextFrame(stack, arg, index);
    }
    StackPushNextFrame(stack);
    if (LambdaExecute(lambda, stack, argCount, exception) == StatusFailure) {
        goto cleanupStack;
    }
    Value *result = StackReturnFromTopFrame(stack);
    SetValue(code, stack, result, false);
    return StatusSuccess;

cleanupStack:
    StackRemoveTopFrame(stack);
returnError:
    return StatusFailure;
}

static inline Status FetchLambda(Byte **code, Stack *stack, Exception *exception) {
    Value *target = GetValue(code, stack);
    Lambda *lambda = ValueLambdaBridge(target);
    Integer32 count = DecodeInteger32VLE(code);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = GetValue(code, stack);
        LambdaSetContextValueAtIndex(lambda, value, index);
    }
    return StatusSuccess;
}

static inline Status FetchList(Byte **code, Stack *stack, Exception *exception) {
    Value *target = GetValue(code, stack);
    List *list = ValueListBridge(target);
    Integer32 count = DecodeInteger32VLE(code);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = GetValue(code, stack);
        ListSetValueAtIndex(list, value, index);
    }
    return StatusSuccess;
}

static inline Status FetchMap(Byte **code, Stack *stack, Exception *exception) {
    Value *target = GetValue(code, stack);
    Map *map = ValueMapBridge(target);
    Integer32 count = DecodeInteger32VLE(code);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *key = GetValue(code, stack);
        Value *value = GetValue(code, stack);
        MapSetValueForKey(map, value, key);
    }
    return StatusSuccess;
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

Status ExecuteCode(Byte *code, Integer32 count, Stack *stack, Exception *exception) {
    while (count > 0) {
        Integer8 opcode = DecodeInteger8FLE(&code);
        if (instruction[opcode](&code, stack, exception) == StatusFailure) {
            goto returnError;
        }
        count -= 1;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}
