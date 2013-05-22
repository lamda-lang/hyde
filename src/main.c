#include "runtime.h"

int main(void) {
  Buffer *buffer = BufferCreate();
  if (buffer == NULL) {
    goto error;
  }
  Stack *stack = StackCreate(1024);
  if (stack == NULL) {
    goto errorBuffer;
  }
  if (!FileRead(FileStandartIn, buffer)) {
    goto errorStack;
  }
  Byte *code = BufferBytes(buffer);
  Integer32Bit registerCount = DecodeVBRInteger32Bit(&code);
  Integer32Bit instructionCount = DecodeVBRInteger32Bit(&code);
  if (!StackBuildNextFrame(stack, registerCount)) {
    goto errorStack;
  }
  StackPushNextFrame(stack);
  if (!ExecuteCode(code, instructionCount, stack)) {
    goto errorStack;
  }
  Value *result = StackReturnFromTopFrame(stack);
  String *string = ValueStringBridge(result);
  LogString(string);
  StackDealloc(stack);
  BufferDealloc(buffer);
  return EXIT_SUCCESS;

errorStack:
  StackDealloc(stack);
errorBuffer:
  BufferDealloc(buffer);
error:
  return EXIT_FAILURE;
}
