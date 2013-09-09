#include <builtin/result.h>

typedef struct Result Result;

struct Result {
    Value *type;
    Value *target;
    Integer8 count;
    Value *args[];
};

static Result *ResultCreate(Value *target, Integer8 count, Error *error) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(Value *) * count, error);
    if (*error != ErrorNone) return NULL;
    result->type = NULL;
    result->target = target;
    result->count = count;
    return result;
}

Value *ResultDecode(Byte **bytes, Error *error) {
    Value *target = DecodeValue(bytes, error);
    if (*error != ErrorNone) goto returnError;
    Integer8 count = DecodeInteger8(bytes);
    Result *result = ResultCreate(target, count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer8 index = 0; index < count; index += 1) {
        result->args[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocResult;
    }
    return result;

deallocResult:
    MemoryDealloc(result);
returnError:
    return NULL;
}
