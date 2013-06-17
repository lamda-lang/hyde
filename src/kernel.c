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
    Integer *integer = ValueIntegerBridge(args[0]);
    Integer *other = ValueIntegerBridge(args[1]);
    Integer *result = IntegerSum(integer, other, error);
    return IntegerValueBridge(result);

returnError:
    return NULL;
}

Value *KernelStringConcatenate(Value **args, Integer8 count, Error *error) {
    Type types[] = {TypeString, TypeString};
    if (!Valid(args, types, count, 2, error)) {
	goto returnError;
    }
    String *string = ValueStringBridge(args[0]);
    String *other = ValueStringBridge(args[1]);
    String *result = StringConcatenate(string, other, error);
    return StringValueBridge(result);

returnError:
    return NULL;
}
