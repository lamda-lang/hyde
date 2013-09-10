#include <builtin/result.h>

typedef struct Result Result;

struct Result {
    Value *target;
    Integer8 count;
    Value *args[];
};

static Result *ResultCreate(Value *target, Integer8 count) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(Value *) * count);
    if (result == NULL)
        return NULL;
    result->target = target;
    result->count = count;
    return result;
}

Value *ResultDecode(Byte **bytes, Error *error) {
    Value *target = DecodeValue(bytes, error);
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
    return ValueCreate(ModelResult, result);
}
void ResultRelease(void *resultData) {
    MemoryDealloc(resultData);
}

Bool ResultEqual(void *resultData, void *otherData) {
    Result *result = resultData;
    Result *other = otherData;
    if (result->count != other->count && !ValueEqual(result->target, other->target))
        return FALSE;
    for (Integer8 index = 0; index < result->count; index += 1)
        if (!ValueEqual(result->args[index], other->args[index])
            return FALSE;
    return TRUE;
}
