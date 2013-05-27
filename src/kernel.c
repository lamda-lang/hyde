#include "kernel.h"

Status KernelIntegerSum(Stack *stack, Exception *exception) {
    Value *arg[] = {StackGetArgFromTopFrame(stack, 0), StackGetArgFromTopFrame(stack, 1)};
    Integer *integer = ValueIntegerBridge(arg[0]);
    Integer *other = ValueIntegerBridge(arg[1]);
    Integer *new = IntegerSum(integer, other, exception);
    if (new == NULL) {
        goto returnError;
    }
    Value *result = IntegerValueBridge(new);
    StackSetResultInTopFrame(stack, result);
    return StatusSuccess;

returnError:
  return StatusFailure;
}

Status KernelStringConcatenate(Stack *stack, Exception *exception) {
    Value *arg[] = {StackGetArgFromTopFrame(stack, 0), StackGetArgFromTopFrame(stack, 1)};
    String *string = ValueStringBridge(arg[0]);
    String *other = ValueStringBridge(arg[1]);
    String *new = StringConcatenate(string, other, exception);
    if (new == NULL) {
        goto returnError;
    }
    Value *result = StringValueBridge(new);
    StackSetResultInTopFrame(stack, result);
    return StatusSuccess;

returnError:
    return StatusFailure;
}
