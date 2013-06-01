#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack, Error *error);

static inline Value *GetValue(Byte **code, Stack *stack) {
    Integer32 index = DecodeInteger32VLE(code);
    return StackValuesFromTopFrame(stack)[index];
}

static inline void SetValue(Byte **code, Stack *stack, Value *value, bool transient) {
    Integer32 index = DecodeInteger32VLE(code);
    ValueSetFlag(value, FlagGarbage, transient);
    StackValuesFromTopFrame(stack)[index] = value;
}

static inline Status CreateBooleanTrue(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanTrueSingleton();
    Value *booleanValue = BooleanValueBridge(boolean);
    SetValue(code, stack, booleanValue, false);
    return StatusSuccess;
}

static inline Status CreateBooleanFalse(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanFalseSingleton();
    Value *booleanValue = BooleanValueBridge(boolean);
    SetValue(code, stack, booleanValue, false);
    return StatusSuccess;
}

static inline Status CreateDo(Byte **code, Stack *stack, Error *error) {
    Do *block = DoDecode(code, error);
    if (block == NULL) {
	goto returnError;
    }
    Value **values = StackValuesFromTopFrame(stack);
    DoFetchContext(block, values, code);
    Value *doValue = DoValueBridge(block);
    SetValue(code, stack, doValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateIdentifier(Byte **code, Stack *stack, Error *error) {
    Identifier *id = IdentifierDecode(code, error);
    if (id == NULL) {
        goto returnError;
    }
    Value *idValue = IdentifierValueBridge(id);
    SetValue(code, stack, idValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateInteger(Byte **code, Stack *stack, Error *error) {
    Integer *integer = IntegerDecode(code, error);
    if (integer == NULL) {
        goto returnError;
    }
    Value *integerValue = IntegerValueBridge(integer);
    SetValue(code, stack, integerValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateLambda(Byte **code, Stack *stack, Error *error) {
    Lambda *lambda = LambdaDecode(code, error);
    if (lambda == NULL) {
        goto returnError;
    }
    Value **values = StackValuesFromTopFrame(stack);
    LambdaFetch(lambda, values, code);
    Value *lambdaValue = LambdaValueBridge(lambda);
    SetValue(code, stack, lambdaValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateList(Byte **code, Stack *stack, Error *error) {
    List *list = ListDecode(code, error);
    if (list == NULL) {
        goto returnError;
    }
    Value *listValue = ListValueBridge(list);
    SetValue(code, stack, listValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateMap(Byte **code, Stack *stack, Error *error) {
    Map *map = MapDecode(code, error);
    if (map == NULL) {
        goto returnError;
    }
    Value *mapValue = MapValueBridge(map);
    SetValue(code, stack, mapValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateNil(Byte **code, Stack *stack, Error *error) {
    Value *nilValue = NilValueBridge();
    SetValue(code, stack, nilValue, false);
    return StatusSuccess;
}

static inline Status CreateString(Byte **code, Stack *stack, Error *error) {
    String *string = StringDecode(code, error);
    if (string == NULL) {
        goto returnError;
    }
    Value *stringValue = StringValueBridge(string);
    SetValue(code, stack, stringValue, true);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status ApplyArg(Byte **code, Stack *stack, Error *error) {
    Value *target = GetValue(code, stack);
    if (ValueType(target) != TypeLambda) {
	*error = ErrorInvalidType;
        goto returnError;
    }
    Lambda *lambda = ValueLambdaBridge(target);
    if (LambdaExecute(lambda, code, stack, error) == StatusFailure) {
        goto returnError;
    }
    Value *result = *StackResultFromTopFrame(stack);
    SetValue(code, stack, result, false);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status FetchList(Byte **code, Stack *stack, Error *error) {
    Value *target = GetValue(code, stack);
    List *list = ValueListBridge(target);
    Value **values = StackValuesFromTopFrame(stack);
    ListFetch(list, values, code);
    return StatusSuccess;
}

static inline Status FetchMap(Byte **code, Stack *stack, Error *error) {
    Value *target = GetValue(code, stack);
    Map *map = ValueMapBridge(target);
    Value **values = StackValuesFromTopFrame(stack);
    MapFetch(map, values, code);
    return StatusSuccess;
}

static Instruction *instruction[] = {
    [0] = CreateBooleanTrue,
    [1] = CreateBooleanFalse,
    [2] = CreateDo,
    [3] = CreateIdentifier,
    [4] = CreateInteger,
    [5] = CreateLambda,
    [6] = CreateList,
    [7] = CreateMap,
    [8] = CreateNil,
    [9] = CreateString,
    [10] = ApplyArg,
    [11] = FetchList,
    [12] = FetchMap
};

Status ExecuteCode(Byte *code, Integer32 count, Stack *stack, Error *error) {
    while (count > 0) {
        Integer8 opcode = DecodeInteger8FLE(&code);
        if (instruction[opcode](&code, stack, error) == StatusFailure) {
            goto returnError;
        }
        count -= 1;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}
