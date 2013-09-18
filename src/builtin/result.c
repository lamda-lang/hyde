#include <builtin/result.h>

struct Result {
    Value *target;
    Integer8 count;
    Value *args[];
};

static Value *args[256] = {NULL};

static Result *ResultCreate(Value *target, Integer8 count) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(Value *) * count);
    if (result == NULL)
        return NULL;
    result->target = target;
    result->count = count;
    return result;
}

Result *ResultDecode(Byte **bytes) {
    Value *target = ValueDecode(bytes);
    if (target == NULL)
        return NULL;
    Integer8 count = DecodeInteger8(bytes);
    Result *result = ResultCreate(target, count);
    if (result == NULL)
        return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return ResultRelease(result), NULL;
        result->args[index] = value;
    }
    return result;
}

Value *ResultEval(Result *result, Value *context) {
    Value *target = ValueEval(result->target, context);
    if (target == NULL)
        return NULL;
    for (Integer8 index = 0; index < result->count; index += 1) {
        Value *arg = ValueEval(result->args[index], context);
        if (arg == NULL)
            return NULL;
        args[index] = arg;
    }
    return ValueCall(target, args, result->count);
}

Value *ResultEqual(Result *result, Result *other) {
    if (result->count != other->count)
        return VALUE_FALSE;
    if (ValueEqual(result->target, other->target) == VALUE_FALSE)
        return VALUE_FALSE;
    for (Integer8 index = 0; index < result->count; index += 1)
        if (ValueEqual(result->args[index], other->args[index]) == VALUE_FALSE)
            return VALUE_FALSE;
    return VALUE_TRUE;
}

Size ResultRelease(Result *result) {
    Integer8 count = result->count;
    MemoryDealloc(result);
    return sizeof(Result) + sizeof(Value *) * count;
}
