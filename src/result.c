#include "result.h"

struct Result {
    Value base;
    Integer8 count;
    Element lamda;
    Element arg[];
};

static Result *Create(Integer32 lamdaIndex, Integer8 count, Error *error) {
    Result *result = MemoryAlloc(sizeof(Result) + sizeof(Element) * count, error);
    if (result == NULL) {
	goto returnError;
    }
    result->base = TypeResult;
    result->count = count;
    result->lamda.index = lamdaIndex;
    return result;

returnError:
    return NULL;
}

Value *ResultValueBridge(Result *result) {
    return (Value *)result;
}

Value *ResultDecode(Byte **bytes, Error *error) {
    Integer32 lamdaIndex = DecodeInteger32VLE(bytes);
    Integer8 argCount = DecodeInteger8FLE(bytes);
    Result *result = Create(lamdaIndex, argCount, error);
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
    result->lamda.value = values[result->lamda.index];
    for (Integer8 index = 0; index < result->count; index += 1) {
	Integer32 argIndex = result->arg[index].index;
	result->arg[index].value = values[argIndex];
    }
}

void ResultDealloc(Value *resultValue) {
    MemoryDealloc(resultValue);
}

Value *ResultEval(Value *resultValue, bool pure, Error *error) {
    Result *result = ValueResultBridge(resultValue);
    Value *lamdaValue = ValueEval(result->lamda.value, true, error);
    if (lamdaValue == NULL) {
	goto returnError;
    }
    if (ValueType(lamdaValue) != TypeLamda) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    Lamda *lamda = ValueLamdaBridge(lamdaValue);
    for (Integer8 index = 0; index < result->count; index += 1) {
	Value *arg = ValueEval(result->arg[index].value, true, error);
	if (arg == NULL) {
	    goto returnError;
	}
	result->arg[index].value = arg;
    }
    Value *value = LamdaResult(lamda, &result->arg[0].value, result->count, error);
    if (value == NULL) {
	goto returnError;
    }
    return ValueEval(value, pure, error);

returnError:
    return NULL;
}
