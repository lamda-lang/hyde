#include "runtime.h"

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
  RTLogString(string);
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
