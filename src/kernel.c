#include "kernel.h"

Status KernelIntegerSum(Stack *stack, Error *error) {
    Value **arg = StackArgsFromTopFrame(stack);
    Integer *integer = ValueIntegerBridge(arg[0]);
    Integer *other = ValueIntegerBridge(arg[1]);
    Integer *new = IntegerSum(integer, other, error);
    if (new == NULL) {
        goto returnError;
    }
    *StackResultFromTopFrame(stack) = IntegerValueBridge(new);
    return StatusSuccess;

returnError:
  return StatusFailure;
}

Status KernelStringConcatenate(Stack *stack, Error *error) {
    Value **arg = StackArgsFromTopFrame(stack);
    String *string = ValueStringBridge(arg[0]);
    String *other = ValueStringBridge(arg[1]);
    String *new = StringConcatenate(string, other, error);
    if (new == NULL) {
        goto returnError;
    }
    *StackResultFromTopFrame(stack) = StringValueBridge(new);
    return StatusSuccess;

returnError:
    return StatusFailure;
}
