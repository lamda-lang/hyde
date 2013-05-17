#include "runtime.h"

static inline void Exit(RTData *data, RTStack *stack, RTError error) {
  if (data != NULL) RTDataDealloc(data);
  if (stack != NULL) RTStackDealloc(stack);
  RTErrorShow(error);
  RTProcessExitFailure();
}

int main(void) {
  RTData *data = RTDataCreate();
  RTStack *stack = RTStackCreate(1024);
  if (data == NULL || stack == NULL) Exit(data, stack, RTErrorOutOfMemory);
  RTError readError = RTFileRead(RTFileStandartIn, data);
  if (readError != RTErrorNone) Exit(data, stack, readError);
  RTByte *code = RTDataBytes(data);
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(&code);
  RTError buildError = RTStackBuildNextFrame(stack, registerCount);
  if (buildError != RTErrorNone) Exit(data, stack, buildError);
  RTStackPushNextFrame(stack);
  RTError codeError = RTExecuteCode(code, instructionCount, stack);
  if (codeError != RTErrorNone) Exit(data, stack, codeError);
  RTValue *result = RTStackReturnFromTopFrame(stack);
}
