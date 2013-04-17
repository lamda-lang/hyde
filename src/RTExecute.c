#include "RTExecute.h"

static inline void DeallocValueSet(RTValue *reg, RTInteger32Bit from, RTInteger32Bit until) {
  for (RTInteger32Bit index = from; index < until; index += 1) {
    RTValueDealloc(reg[index]);
  }
}

RTValue RTExecuteCode(RTByte *code, RTValue *arg, RTInteger8Bit argCount) {
  RTInteger32Bit regCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instCount = RTDecodeVBRInteger32Bit(&code);
  RTValue *reg = RTMemoryAlloc(SIZE_OF(RTValue *, regCount));
  if (reg == NULL) {
    return NULL;
  }
  for (RTInteger8Bit index = 0; index < argCount; index += 1) {
    reg[index] = arg[index];
  }
  for (RTInteger32Bit index = argCount; index < regCount; index += 1) {
    reg[index] = RTValueCreate();
    if (reg[index] == NULL) {
      DeallocValueSet(reg, argCount, index);
      RTMemoryDealloc(reg);
      return NULL;
    }
  }
  for (RTInteger32Bit index = 0; index < instCount; index += 1) {
    if (RTOperationExecute(&code, reg) == FALSE) {
      DeallocValueSet(reg, argCount, regCount);
      return NULL;
    }
  }
  RTValue result = reg[argCount];
  RTMemoryDealloc(reg);
  return result;
}
