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

Value *ResultDecodePrimitive(Binary *binary, Integer32 *offset) {
    Value *target = BinaryDecodeValue(binary, offset);
    if (target == NULL)
        return NULL;
    Integer8 count;
    if (!BinaryDecodeInteger8(binary, offset, &count))
        return NULL;
    Result *result = ResultCreate(count);
    for (Integer8 index = 0; index < count; index += 1) {
        Value *arg = BinaryDecodeValue(binary, offset);
        if (arg == NULL)
            goto out;
        result->args[index] = arg;
    }
    return ValueCreateResult(result);

out:
    ResultDealloc(result);
    return NULL;
}
