#include "RTDecode.h"
#include "RTExecute.h"
#include "RTMemoryAlloc.h"
#include "RTOperation.h"

enum {
  CREATE_IDENTIFIER = 0,
  CREATE_LIST = 1,
  CREATE_MODULE = 2,
  CREATE_STRING = 3
};

static inline void DeallocRegisterSet(RTValue *registerSet, RTInteger32Bit count) {
  for (RTIndex index = 0; index < count; index += 1) {
    RTValueDealloc(registerSet[index]);
  }
  RTModuleDealloc(registerSet);
}

static inline RTValue *CreateRegisterSet(RTInteger32Bit count) {
  RTValue *registerSet = RTMemoryAlloc(SIZE_OF(RTValue, count));
  if (registerSet == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTValue value = RTValueCreate();
    if (value == NULL) {
      DeallocRegisterSet(registerSet, index);
      return NULL;
    }
    registerSet[index] = value;
  }
  return registerSet;
}

static inline void ExecuteInstruction(RTByte **instruction, RTValue *registerSet, RTInteger32Bit index) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(instruction);
  switch (opcode) {
  case CREATE_IDENTIFIER:
    return;
  case CREATE_LIST:
    return;
  case CREATE_MODULE:
    return;
  case CREATE_STRING:
    return;
  }
}

RTValue RTExecuteBytecode(RTByte *code) {
  RTInteger32Bit registerCount = RTDecodeVBRInteger32Bit(&code);
  RTInteger32Bit instructionCount = RTDecodeVBRInteger32Bit(&code);
  RTValue *registerSet = CreateRegisterSet(registerCount);
  if (registerSet == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < instructionCount; index += 1) {
    ExecuteInstruction(&code, registerSet, index);
  }
  RTValue result = registerSet[0];
  DeallocRegisterSet(registerSet, 0);
  return result;
}

#ifdef RT_EXECUTE_TEST

int main(void) {

}

#endif
