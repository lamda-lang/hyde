#include "RTKernel.h"

RTError RTKernelStringConcatenate(RTInteger8Bit arity, RTStack *stack) {
  RTValue *arg[] = {RTStackGetArgFromTopFrame(stack, 0), RTStackGetArgFromTopFrame(stack, 1)};
  if (arity != 2) return RTErrorArityMismatch;
  if (RTValueType(arg[0]) != RTTypeString) return RTErrorInvalidType;
  if (RTValueType(arg[1]) != RTTypeString) return RTErrorInvalidType;
  RTString *string = RTValueStringBridge(arg[0]);
  RTString *other = RTValueStringBridge(arg[1]);
  RTString *new = RTStringConcatenate(string, other);
  if (new == NULL) return RTErrorOutOfMemory;
  RTValue *result = RTStringValueBridge(new);
  RTStackSetResultInTopFrame(stack, result);
  return RTErrorNone;
}
