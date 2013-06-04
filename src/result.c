#include "result.h"

struct Result {
    Value base;
    Lambda *lambda;
    Integer8 arity;
    Value *arg[];
};

Value *ResultValueBridge(Result *result) {
    return (Value *)result;
}

Result *ResultDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Size size = sizeof(Result) + sizeof(Value *) * arity;
    Result *result = MemoryAlloc(size, error);
    if (result == NULL) {
	goto returnError;
    }
    result->base = TypeResult;
    result->arity = arity;
    return result;

returnError:
    return NULL;
}

void ResultDealloc(Result *result) {
    MemoryDealloc(result);
}

Integer8 ResultArity(Result *result) {
    return result->arity;
}

void ResultSetLambda(Result *result, Lambda *lambda) {
    result->lambda = lambda;
}

void ResultSetArgAtIndex(Result *result, Value *arg, Integer8 index) {
    result->arg[index] = arg;
}
