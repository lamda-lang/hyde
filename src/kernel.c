#include "kernel.h"


static bool Valid(Value **args, Type *types, Integer8 count, Integer8 arity, Error *error) {
    if (count != arity) {
	*error = ErrorArityMismatch;
	goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
	if (ValueType(args[index]) != types[index]) {
	    *error = ErrorInvalidType;
	    goto returnError;
	}
    }
    return true;

returnError:
    return false;
}

Value *KernelIntegerSum(Value **args, Integer8 count, Error *error) {
    Type types[] = {TypeInteger, TypeInteger};
    if (!Valid(args, types, count, 2, error)) {
	goto returnError;
    }
    return IntegerSum(args[0], args[1], error);

returnError:
    return NULL;
}

Value *KernelStringConcatenate(Value **args, Integer8 count, Error *error) {
    Type types[] = {TypeString, TypeString};
    if (!Valid(args, types, count, 2, error)) {
	goto returnError;
    }
    return StringConcatenate(args[0], args[1], error);

returnError:
    return NULL;
}
