#include "kernel.h"

Status KernelStringConcatenate(Integer8Bit arity, Stack *stack) {
  Value *arg[] = {StackGetArgFromTopFrame(stack, 0), StackGetArgFromTopFrame(stack, 1)};
  if (arity != 2 || ValueType(arg[0]) != TypeString || ValueType(arg[1]) != TypeString) {
    goto error;
  }
  String *string = ValueStringBridge(arg[0]);
  String *other = ValueStringBridge(arg[1]);
  String *new = StringConcatenate(string, other);
  if (new == NULL) {
    goto error;
  }
  Value *result = StringValueBridge(new);
  StackSetResultInTopFrame(stack, result);
  return StatusSuccess;

error:
  return StatusFailure;
}
