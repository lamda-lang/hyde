#include <builtin/result.h>

typedef struct Result Result;

struct Result {
    VALUE *type;
    VALUE *target;
    Integer8 count;
    VALUE *args[];
};

static Result *ResultCreate(VALUE *target, Integer8 count, Error *error) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) return NULL;
    result->type = RuntimeValueForConstant(ConstantResultType);
    result->target = target;
    result->count = count;
    return result;
}

VALUE *ResultDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8(bytes);
    VALUE *target = DecodeValue(bytes, error);
    if (*error != ErrorNone) goto returnError;
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
