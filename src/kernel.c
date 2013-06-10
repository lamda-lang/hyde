#include "kernel.h"

Value *KernelIntegerSum(Value **args, Integer8 count, Error *error) {
    Integer *integer = ValueIntegerBridge(args[0]);
    Integer *other = ValueIntegerBridge(args[1]);
    Integer *result = IntegerSum(integer, other, error);
    return IntegerValueBridge(result);
}

Value *KernelStringConcatenate(Value **args, Integer8 count, Error *error) {
    String *string = ValueStringBridge(args[0]);
    String *other = ValueStringBridge(args[1]);
    String *result = StringConcatenate(string, other, error);
    return StringValueBridge(result);
}
