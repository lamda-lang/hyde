#include "kernel.h"

Value *KernelIntegerSum(Args *args, Error *error) {
    Value **arg = ArgsValues(args);
    Integer *integer = ValueIntegerBridge(arg[0], NULL);
    Integer *other = ValueIntegerBridge(arg[1], NULL);
    Integer *result = IntegerSum(integer, other, error);
    return IntegerValueBridge(result);
}

Value *KernelStringConcatenate(Args *args, Error *error) {
    Value **arg = ArgsValues(args);
    String *string = ValueStringBridge(arg[0], NULL);
    String *other = ValueStringBridge(arg[1], NULL);
    String *result = StringConcatenate(string, other, error);
    return StringValueBridge(result);
}
