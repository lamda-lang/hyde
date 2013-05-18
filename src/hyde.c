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

static inline RTError RTLog(RTString *string) {
  RTBuffer *buffer = RTBufferCreate();
  if (buffer == NULL) return RTErrorOutOfMemory;
  RTError encodeError = RTStringEncodeASCII(string, buffer);
  if (encodeError != RTErrorNone) return encodeError;
  RTInteger8Bit newline = '\n';
  RTError appendError = RTBufferAppend(buffer, &newline, sizeof(newline));
  if (appendError != RTErrorNone) return appendError;
  RTError writeError = RTFileWrite(RTFileStandartOut, buffer);
  RTBufferDealloc(buffer);
  return writeError;
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
  RTError logError = RTLog(string);
  Exit(buffer, stack, result, logError);
}
