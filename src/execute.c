#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack, Error *error);

static Value **DecodeFrameValue(Byte **code, Stack *stack) {
    return StackFrameValues(stack) + DecodeInteger32VLE(code);
}

static Status CreateNil(Byte **code, Stack *stack, Error *error) {
    *DecodeFrameValue(code, stack) = NilValueBridge();
    return StatusSuccess;
}

static Status CreateBooleanTrue(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanTrueSingleton();
    *DecodeFrameValue(code, stack) = BooleanValueBridge(boolean);
    return StatusSuccess;
}

static Status CreateBooleanFalse(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanFalseSingleton();
    *DecodeFrameValue(code, stack) = BooleanValueBridge(boolean);
    return StatusSuccess;
}

static Status CreateInteger(Byte **code, Stack *stack, Error *error) {
    Integer *integer = IntegerDecode(code, error);
    if (integer == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = IntegerValueBridge(integer);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateFloat(Byte **code, Stack *stack, Error *error) {
    Float *fpv = FloatDecode(code, error);
    if (fpv == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = FloatValueBridge(fpv);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateIdentifier(Byte **code, Stack *stack, Error *error) {
    Identifier *id = IdentifierDecode(code, error);
    if (id == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = IdentifierValueBridge(id);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateString(Byte **code, Stack *stack, Error *error) {
    String *string = StringDecode(code, error);
    if (string == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = StringValueBridge(string);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateRange(Byte **code, Stack *stack, Error *error) {
    Range *range = RangeCreate(error);
    if (range == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = RangeValueBridge(range);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateSet(Byte **code, Stack *stack, Error *error) {
    Set *set = SetDecode(code, error);
    if (set == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = SetValueBridge(set);
    return StatusSuccess;

returnError:
    return StatusFailure;
}
static Status CreateList(Byte **code, Stack *stack, Error *error) {
    List *list = ListDecode(code, error);
    if (list == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = ListValueBridge(list);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateMap(Byte **code, Stack *stack, Error *error) {
    Map *map = MapDecode(code, error);
    if (map == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = MapValueBridge(map);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateLambda(Byte **code, Stack *stack, Error *error) {
    Lambda *lambda = LambdaDecode(code, error);
    if (lambda == NULL) {
        goto returnError;
    }
    Integer8 contextLength = LambdaContextLength(lambda);
    for (Integer8 index = 0; index < contextLength; index += 1) {
	Value *contextValue = *DecodeFrameValue(code, stack);
	LambdaSetContextValueAtIndex(lambda, contextValue, index);
    }
    *DecodeFrameValue(code, stack) = LambdaValueBridge(lambda);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateDo(Byte **code, Stack *stack, Error *error) {
    Do *block = DoDecode(code, error);
    if (block == NULL) {
	goto returnError;
    }
    Integer8 contextCount = DoContextCount(block);
    for (Integer8 index = 0; index < contextCount; index += 1) {
	Value *value = *DecodeFrameValue(code, stack);
	DoSetContextValueAtIndex(block, value, index);
    }
    *DecodeFrameValue(code, stack) = DoValueBridge(block);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Status CreateResult(Byte **code, Stack *stack, Error *error) {
    Value *value = *DecodeFrameValue(code, stack);
    Lambda *lambda = ValueLambdaBridge(value, error);
    if (lambda == NULL) {
	goto returnError;
    }
    Args *args = ArgsDecode(code, error);
    if (args == NULL) {
	goto returnError;
    }
    Integer8 argCount = ArgsCount(args);
    for (Integer8 index = 0; index < argCount; index += 1) {
	ArgsValues(args)[index] = *DecodeFrameValue(code, stack);
    }
    Value *result = LambdaExecute(lambda, args, stack, error);
    if (result == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = result;
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static Instruction *instruction[] = {
    [0] = CreateNil,
    [1] = CreateBooleanTrue,
    [2] = CreateBooleanFalse,
    [3] = CreateInteger,
    [4] = CreateFloat,
    [5] = CreateIdentifier,
    [6] = CreateString,
    [7] = CreateRange,
    [8] = CreateSet,
    [9] = CreateList,
    [10] = CreateMap,
    [11] = CreateLambda,
    [12] = CreateDo,
    [13] = CreateResult
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
