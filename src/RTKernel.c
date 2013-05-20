#include "RTKernel.h"

RTStatus RTKernelStringConcatenate(RTInteger8Bit arity, RTStack *stack) {
  RTValue *arg[] = {RTStackGetArgFromTopFrame(stack, 0), RTStackGetArgFromTopFrame(stack, 1)};
  if (arity != 2 || RTValueType(arg[0]) != RTTypeString || RTValueType(arg[1]) != RTTypeString) {
    goto error;
  }
  RTString *string = RTValueStringBridge(arg[0]);
  RTString *other = RTValueStringBridge(arg[1]);
  RTString *new = RTStringConcatenate(string, other);
  if (new == NULL) {
    goto error;
  }
  RTValue *result = RTStringValueBridge(new);
  RTStackSetResultInTopFrame(stack, result);
  return RTStatusSuccess;

error:
  return RTStatusFailure;
}
