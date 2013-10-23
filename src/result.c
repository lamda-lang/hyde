#include "result.h"

struct Result {
    Value *target;
    Integer8 count;
    Value *args[];
};

static Value *args[256] = {NULL};

static Result *ResultCreate(Integer8 count) {
    Result *result = MemoryAllocRegion(sizeof(Result), sizeof(Value *), count);
    result->count = count;
    return result;
}

static void ResultDealloc(Result *result) {
    MemoryDealloc(result);
}

Bool ResultDecode(Binary *binary, Integer32 *offset, Value **value) {
    Value *target;
    Integer8 count;
    if (!BinaryDecodeValue(binary, offset, &target))
        return FALSE;
    if (!BinaryDecodeInteger8(binary, offset, &count))
        return FALSE;
    Result *result = ResultCreate(count);
    for (Integer8 index = 0; index < count; index += 1) {
        Value *arg;
        if (!BinaryDecodeValue(binary, offset, &arg))
            goto out;
        result->args[index] = arg;
    }
    *value = ValueCreateResult(result);
    return TRUE;

out:
    ResultDealloc(result);
    return FALSE;
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
