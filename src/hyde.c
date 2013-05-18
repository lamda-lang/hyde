#include "runtime.h"

static inline void Exit(RTBuffer *buffer, RTStack *stack, RTValue *result, RTError error) {
  if (buffer != NULL) RTBufferDealloc(buffer);
  if (stack != NULL) RTStackDealloc(stack);
  if (result != NULL) RTValueDealloc(result);
  if (error == RTErrorNone) {
    RTProcessExitSuccess();
  } 
  RTErrorShow(error);
  RTProcessExitFailure();
}

int main(void) {
  RTBuffer *buffer = RTBufferCreate();
  RTStack *stack = RTStackCreate(1024);
  if (buffer == NULL || stack == NULL) Exit(buffer, stack, NULL, RTErrorOutOfMemory);
  RTError readError = RTFileRead(RTFileStandartIn, buffer);
  if (readError != RTErrorNone) Exit(buffer, stack, NULL, readError);
  RTByte *code = RTBufferBytes(buffer);
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(&code);
  RTError buildError = RTStackBuildNextFrame(stack, registerCount);
  if (buildError != RTErrorNone) Exit(buffer, stack, NULL, buildError);
  RTStackPushNextFrame(stack);
  RTError codeError = RTExecuteCode(code, instructionCount, stack);
  if (codeError != RTErrorNone) Exit(buffer, stack, NULL, codeError);
  RTValue *result = RTStackReturnFromTopFrame(stack);
  RTString *string = RTValueStringBridge(result);
  RTError writeError = RTStringWriteToFile(string, RTFileStandartOut);
  if (writeError != RTErrorNone) Exit(buffer, stack, result, writeError);
  Exit(buffer, stack, result, RTErrorNone);
}
