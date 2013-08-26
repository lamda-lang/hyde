#include "result.h"

struct Result {
    Type *type;
    VALUE *target;
    Integer8 count;
    VALUE *args[];
};

static Result *ResultCreate(VALUE *target, Integer8 count, VALUE **error) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    result->type = RuntimeResultType;
    result->target = target;
    result->count = count;
    return result;
}

VALUE *ResultDecode(Byte **bytes, VALUE **error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    VALUE *target = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    Result *result = ResultCreate(target, count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
        result->args[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocResult;
        }
    }
    return BridgeFromResult(result);

deallocResult:
    MemoryDealloc(result);
returnError:
    return NULL;
}
