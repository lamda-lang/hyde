#include "kernel.h"

Value *KernelIntegerSum(Value **args, Integer8 count, Error *error) {
    Integer *integer = ValueIntegerBridge(args[0], NULL);
    Integer *other = ValueIntegerBridge(args[1], NULL);
    Integer *result = IntegerSum(integer, other, error);
    return IntegerValueBridge(result);
}

Value *KernelStringConcatenate(Value **args, Integer8 count, Error *error) {
    String *string = ValueStringBridge(args[0], NULL);
    String *other = ValueStringBridge(args[1], NULL);
    String *result = StringConcatenate(string, other, error);
    return StringValueBridge(result);
}
