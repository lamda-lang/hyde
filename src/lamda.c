#include "runtime.h"

int main(void) {
  RTData *data = RTDataCreate();
  RTFileRead(RTFileStandartIn, data);
  RTByte *code = RTDataBytes(data);
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(&code);
  RTStack *stack = RTStackCreate(1024);
  RTStackBuildNextFrame(stack, registerCount);
  RTStackPushNextFrame(stack);
  RTExecuteCode(code, instructionCount, stack);
  RTValue *result = RTStackReturnFromTopFrame(stack);
}
