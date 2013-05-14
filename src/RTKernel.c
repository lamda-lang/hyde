#include "RTKernel.h"

#define GUARD_ARITY(arity, count) if (arity != count) return RTErrorArityMismatch
#define GUARD_ARG(arg, type) if (RTValueType(arg) != type) return RTErrorInvalidType

RTError RTKernelEqual(RTInteger8Bit arity, RTStack *stack) {
  GUARD_ARITY(arity, 2);
  RTValue *arg[] = {RTStackGetArgFromTopFrame(stack, 0), RTStackGetArgFromTopFrame(stack, 1)};
  bool equal = RTValueEqual(arg[0], arg[1]);
  RTBoolean *boolean = RTBooleanCreate(equal);
  if (boolean == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *result = RTBooleanValueBridge(boolean);
  RTStackSetResultInTopFrame(stack, result);
  return RTErrorNone;
}

RTError RTKernelStringConcatenate(RTInteger8Bit arity, RTStack *stack) {
  GUARD_ARITY(arity, 2);
  RTValue *arg[] = {RTStackGetArgFromTopFrame(stack, 0), RTStackGetArgFromTopFrame(stack, 1)};
  GUARD_ARG(arg[0], RTTypeString);
  GUARD_ARG(arg[1], RTTypeString);
  RTString *string = RTValueStringBridge(arg[0]);
  RTString *other = RTValueStringBridge(arg[1]);
  RTString *new = RTStringConcatenate(string, other);
  if (new == NULL) {
    return RTErrorOutOfMemory;
  }
  RTValue *result = RTStringValueBridge(new);
  RTStackSetResultInTopFrame(stack, result);
  return RTErrorNone;
}
