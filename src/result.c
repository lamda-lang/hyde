#include "result.h"

struct Result {
    Value *target;
    Integer8 count;
    Value *args[];
};

static Value *args[256] = {NULL};

static Size ResultSizeOf(Integer8 count) {
    return sizeof(Result) + sizeof(Value *) * count;
}

static Result *ResultCreate(Value *target, Integer8 count, Error *error) {
    Size size = ResultSizeOf(count);
    Result *result = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    result->target = target;
    result->count = count;
    return result;
}

Size ResultSize(Result *result) {
    Size size = ValueSize(result->target) + INTEGER_8_SIZE;
    for (Integer8 index = 0; index < result->count; index += 1)
        size += ValueSize(result->args[index]);
    return size;
}

Size ResultEncode(Result *result, Byte **bytes) {
    ValueEncode(result->target, bytes);
    EncodeInteger8(result->count, bytes);
    for (Integer8 index = 0; index < result->count; index += 1)
        ValueEncode(result->args[index], bytes);
    return ResultSize(result);
}

Result *ResultDecode(Byte **bytes, Error *error) {
    Value *target = ValueDecode(bytes, error);
    if (ERROR(error))
        return NULL;
    Integer8 count = DecodeInteger8(bytes);
    Result *result = ResultCreate(target, count, error);
    if (ERROR(error))
        return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        result->args[index] = ValueDecode(bytes, error);
        if (ERROR(error))
            goto result;
    }
    return result;

result:
    ResultRelease(result);
    return NULL;
}

Value *ResultEval(Value *value, Result *result, Value *context, Error *error) {
    Value *target = ValueEval(result->target, context, error);
    if (ERROR(error))
        return NULL;
    for (Integer8 index = 0; index < result->count; index += 1) {
        args[index] = ValueEval(result->args[index], context, error);
        if (ERROR(error))
            return NULL;
    }
    return ValueCall(target, args, result->count, error);
}

Bool ResultEqual(Result *result, Result *other) {
    if (result->count != other->count)
        return FALSE;
    if (!ValueEqual(result->target, other->target))
        return FALSE;
    for (Integer8 index = 0; index < result->count; index += 1)
        if (!ValueEqual(result->args[index], other->args[index]))
            return FALSE;
    return TRUE;
}

Size ResultRelease(Result *result) {
    Size size = ResultSizeOf(result->count);
    MemoryDealloc(result);
    return size;
}
