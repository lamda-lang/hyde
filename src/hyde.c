#include "runtime.h"

static inline RTStatus Print(RTString *string) {
  RTBuffer *buffer = RTBufferCreate();
  if (buffer == NULL) {
    goto error;
  }
  if (!RTStringEncodeASCII(string, buffer)) {
    goto errorBuffer;
  }
  RTInteger8Bit newline = '\n';
  if (!RTBufferAppend(buffer, &newline, sizeof(newline))) {
    goto errorBuffer;
  }
  if (!RTFileWrite(RTFileStandartOut, buffer)) {
    goto errorBuffer;
  }
  RTBufferDealloc(buffer);
  return RTStatusSuccess;

errorBuffer:
  RTBufferDealloc(buffer);
error:
  return RTStatusFailure;
}

int main(void) {
  RTBuffer *buffer = RTBufferCreate();
  if (buffer == NULL) {
    goto error;
  }
  RTStack *stack = RTStackCreate(1024);
  if (stack == NULL) {
    goto errorBuffer;
  }
  if (!RTFileRead(RTFileStandartIn, buffer)) {
    goto errorStack;
  }
  RTByte *code = RTBufferBytes(buffer);
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(&code);
  if (!RTStackBuildNextFrame(stack, registerCount)) {
    goto errorStack;
  }
  RTStackPushNextFrame(stack);
  if (!RTExecuteCode(code, instructionCount, stack)) {
    goto errorStack;
  }
  RTValue *result = RTStackReturnFromTopFrame(stack);
  RTString *string = RTValueStringBridge(result);
  if (!Print(string)) {
    goto errorStack;
  }
  RTStackDealloc(stack);
  RTBufferDealloc(buffer);
  return EXIT_SUCCESS;

errorStack:
  RTStackDealloc(stack);
errorBuffer:
  RTBufferDealloc(buffer);
error:
  return EXIT_FAILURE;
}
