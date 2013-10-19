#include "result.h"

struct Result {
    Value *target;
    Integer8 count;
    Value *args[];
};

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
