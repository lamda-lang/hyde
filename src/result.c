#include "result.h"

struct Result {
    Value base;
    Integer8 count;
    Element lambda;
    Element arg[];
};

static Result *Create(Integer32 lambdaIndex, Integer8 count, Error *error) {
    Size size = sizeof(Result) + sizeof(Element) * count;
    Result *result = MemoryAlloc(size, error);
    if (result == NULL) {
	goto returnError;
    }
    result->base = TypeResult;
    result->count = count;
    result->lambda.index = lambdaIndex;
    return result;

returnError:
    return NULL;
}

Value *ResultValueBridge(Result *result) {
    return (Value *)result;
}

Value *ResultDecode(Byte **bytes, Error *error) {
    Integer32 lambdaIndex = DecodeInteger32VLE(bytes);
    Integer8 argCount = DecodeInteger8FLE(bytes);
    Result *result = Create(lambdaIndex, argCount, error);
    if (result == NULL) {
	goto returnError;
    }
    for (Integer8 index = 0; index < argCount; index += 1) {
	result->arg[index].index = DecodeInteger32VLE(bytes);
    }
    return ResultValueBridge(result);

returnError:
    return NULL;
}

void ResultFetch(Value *resultValue, Value **values) {
    Result *result = ValueResultBridge(resultValue);
    result->lambda.value = values[result->lambda.index];
    for (Integer8 index = 0; index < result->count; index += 1) {
	Integer32 argIndex = result->arg[index].index;
	result->arg[index].value = values[argIndex];
    }
}

void ResultDealloc(Value *resultValue) {
    MemoryDealloc(resultValue);
}

Value *ResultEval(Value *resultValue, Error *error) {
    Result *result = ValueResultBridge(resultValue);
    Value *lambdaValue = ValueEval(result->lambda.value, error);
    if (lambdaValue == NULL) {
	goto returnError;
    }
    if (ValueType(lambdaValue) != TypeLambda) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    Lambda *lambda = ValueLambdaBridge(lambdaValue);
    for (Integer8 index = 0; index < result->count; index += 1) {
	Value *arg = ValueEval(result->arg[index].value, error);
	if (arg == NULL) {
	    goto returnError;
	}
	result->arg[index].value = arg;
    }
    return LambdaResult(lambda, &result->arg[0].value, result->count, error);

returnError:
    return NULL;
}
