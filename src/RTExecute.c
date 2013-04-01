#include "RTDecode.h"
#include "RTExecute.h"
#include "RTMemory.h"
#include "RTOperation.h"
#include "RTValue.h"

static inline void DeallocRegisterSet(RTValue *reg, RTInteger32Bit count, RTInteger32Bit recursiveCount) {
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    RTValueDealloc(reg[index], index < recursiveCount);
  }
  RTMemoryDealloc(reg);
}

static inline RTValue *CreateRegisterSet(RTInteger32Bit count) {
  RTValue *reg = RTMemoryAlloc(SIZE_OF(RTValue, count));
  if (reg == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < count; index += 1) {
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
  for (RTInteger32Bit index = 0; index < instCount; index += 1) {
    if (RTOperationExecute(&code, reg, index) == FALSE) {
      DeallocRegisterSet(reg, regCount, index);
    }
  }
  RTValue result = reg[0];
  RTMemoryDealloc(reg);
  return result;
}

#ifdef RT_EXECUTE_TEST

static RTValue *FIXTURE_RegisterSet(RTInteger32Bit count) {
  RTValue *reg = CreateRegisterSet(count);
  REQUIRE(reg != NULL);
  return reg;
}

static void TEST_CreateRegisterSet_Valid(void) {
  RTValue *reg = CreateRegisterSet(1);
  REQUIRE(reg != NULL);
  ASSERT(reg[0] != NULL);
}

static void TEST_DeallocRegisterSet_Valid(void) {
  RTValue *reg = FIXTURE_RegisterSet(1);
  DeallocRegisterSet(reg, 1, FALSE);
}

int main(void) {
  TEST_CreateRegisterSet_Valid();
  TEST_DeallocRegisterSet_Valid();
}

#endif
