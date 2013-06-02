#include "execute.h"

typedef Status Instruction(Byte **code, Stack *stack, Error *error);

static inline Value **DecodeFrameValue(Byte **code, Stack *stack) {
    return StackValuesFromTopFrame(stack) + DecodeInteger32VLE(code);
}

static inline Status CreateBooleanTrue(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanTrueSingleton();
    *DecodeFrameValue(code, stack) = BooleanValueBridge(boolean);
    return StatusSuccess;
}

static inline Status CreateBooleanFalse(Byte **code, Stack *stack, Error *error) {
    Boolean *boolean = BooleanFalseSingleton();
    *DecodeFrameValue(code, stack) = BooleanValueBridge(boolean);
    return StatusSuccess;
}

static inline Status CreateDo(Byte **code, Stack *stack, Error *error) {
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

static inline Status CreateFloat(Byte **code, Stack *stack, Error *error) {
    Float *fpv = FloatDecode(code, error);
    if (fpv == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = FloatValueBridge(fpv);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateIdentifier(Byte **code, Stack *stack, Error *error) {
    Identifier *id = IdentifierDecode(code, error);
    if (id == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = IdentifierValueBridge(id);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateInteger(Byte **code, Stack *stack, Error *error) {
    Integer *integer = IntegerDecode(code, error);
    if (integer == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = IntegerValueBridge(integer);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateLambda(Byte **code, Stack *stack, Error *error) {
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

static inline Status CreateList(Byte **code, Stack *stack, Error *error) {
    List *list = ListDecode(code, error);
    if (list == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = ListValueBridge(list);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateMap(Byte **code, Stack *stack, Error *error) {
    Map *map = MapDecode(code, error);
    if (map == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = MapValueBridge(map);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateNil(Byte **code, Stack *stack, Error *error) {
    *DecodeFrameValue(code, stack) = NilValueBridge();
    return StatusSuccess;
}

static inline Status CreateRange(Byte **code, Stack *stack, Error *error) {
    Range *range = RangeCreate(error);
    if (range == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = RangeValueBridge(range);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateSet(Byte **code, Stack *stack, Error *error) {
    Set *set = SetDecode(code, error);
    if (set == NULL) {
	goto returnError;
    }
    *DecodeFrameValue(code, stack) = SetValueBridge(set);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status CreateString(Byte **code, Stack *stack, Error *error) {
    String *string = StringDecode(code, error);
    if (string == NULL) {
        goto returnError;
    }
    *DecodeFrameValue(code, stack) = StringValueBridge(string);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

static inline Status ApplyArg(Byte **code, Stack *stack, Error *error) {
    /* missing */
    return StatusFailure;
}

static inline Status FetchList(Byte **code, Stack *stack, Error *error) {
    Value *listValue = *DecodeFrameValue(code, stack);
    List *list = ValueListBridge(listValue);
    Integer32 length = ListLength(list);
    for (Integer32 index = 0; index < length; index += 1) {
	Value *value = *DecodeFrameValue(code, stack);
        ListSetValueAtIndex(list, value, index);	
    }
    return StatusSuccess;
}

static inline Status FetchMap(Byte **code, Stack *stack, Error *error) {
    Value *mapValue = *DecodeFrameValue(code, stack);
    Map *map = ValueMapBridge(mapValue);
    Integer32 count = MapCount(map);
    for (Integer32 index = 0; index < count; index += 1) {
	Value *key = *DecodeFrameValue(code, stack);
	Value *value = *DecodeFrameValue(code, stack);
	MapSetValueForKey(map, value, key);
    }
    return StatusSuccess;
}

static inline Status FetchRange(Byte **code, Stack *stack, Error *error) {
    Value *rangeValue = *DecodeFrameValue(code, stack);
    Range *range = ValueRangeBridge(rangeValue);
    Value *lower = *DecodeFrameValue(code, stack);
    Value *upper = *DecodeFrameValue(code, stack);
    RangeSetBounds(range, lower, upper);
    return StatusSuccess;
}

static inline Status FetchRangeLower(Byte **code, Stack *stack, Error *error) {
    Value *rangeValue = *DecodeFrameValue(code, stack);
    Range *range = ValueRangeBridge(rangeValue);
    Value *lower = *DecodeFrameValue(code, stack);
    RangeSetBounds(range, lower, NULL);
    return StatusSuccess;
}

static inline Status FetchRangeUpper(Byte **code, Stack *stack, Error *error) {
    Value *rangeValue = *DecodeFrameValue(code, stack);
    Range *range = ValueRangeBridge(rangeValue);
    Value *upper = *DecodeFrameValue(code, stack);
    RangeSetBounds(range, NULL, upper);
    return StatusSuccess;
}

static inline Status FetchSet(Byte **code, Stack *stack, Error *error) {
    Value *setValue = *DecodeFrameValue(code, stack);
    Set *set = ValueSetBridge(setValue);
    Value **values = StackValuesFromTopFrame(stack);
    SetFetch(set, values, code);
    return StatusSuccess;
}

static Instruction *instruction[] = {
    [0] = CreateBooleanTrue,
    [1] = CreateBooleanFalse,
    [2] = CreateDo,
    [3] = CreateFloat,
    [4] = CreateIdentifier,
    [5] = CreateInteger,
    [6] = CreateLambda,
    [7] = CreateList,
    [8] = CreateMap,
    [9] = CreateNil,
    [10] = CreateRange,
    [11] = CreateSet,
    [12] = CreateString,
    [13] = ApplyArg,
    [14] = FetchList,
    [15] = FetchMap,
    [16] = FetchRange,
    [17] = FetchRangeLower,
    [18] = FetchRangeUpper,
    [19] = FetchSet
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
