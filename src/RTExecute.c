#include "RTDecode.h"
#include "RTExecute.h"
#include "RTMemory.h"
#include "RTOperation.h"
#include "RTValue.h"

static inline void DeallocRegisterSet(RTValue *reg, RTInteger32Bit count, RTInteger32Bit recursiveCount) {
  for (RTIndex index = 0; index < count; index += 1) {
    RTValueDealloc(reg[index], index < recursiveCount);
  }
  RTMemoryDealloc(reg);
}

static inline RTValue *CreateRegisterSet(RTInteger32Bit count) {
  RTValue *reg = RTMemoryAlloc(SIZE_OF(RTValue, count));
  if (reg == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < count; index += 1) {
    RTValue value = RTValueCreate();
    if (value == NULL) {
      DeallocRegisterSet(reg, index, 0);
      return NULL;
    }
    reg[index] = value;
  }
  return reg;
}

RTValue RTExecuteBytecode(RTByte *code) {
  RTInteger32Bit regCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instCount = RTDecodeVBRInteger32Bit(&code);
  RTValue *reg = CreateRegisterSet(regCount);
  if (reg == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < instCount; index += 1) {
    if (RTOperationExecute(&code, reg, index) == FALSE) {
      DeallocRegisterSet(reg, regCount, index);
    }
  }
  RTValue result = reg[0];
  RTMemoryDealloc(reg);
  return result;
}
