#include "RTDecode.h"
#include "RTExecute.h"
#include "RTMemory.h"
#include "RTValue.h"

enum {
  CREATE_IDENTIFIER = 0,
  CREATE_LIST = 1,
  CREATE_MODULE = 2,
  CREATE_STRING = 3
};

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
    if (ExecuteInstruction(&code, reg, index) == FALSE) {
      DeallocRegisterSet(reg, regCount, index);
    }
    reg[index] = result;
  }
  RTValue result = reg[0];
  RTMemoryDealloc(reg);
  return result;
}

#ifdef RT_EXECUTE_TEST

RTValue *FIXTURE_RegisterSet(RTInteger32Bit count) {
  RTValue *reg = CreateRegisterSet(count);
  REQUIRE(reg != NULL);
  return reg;
}

RTIdentifier FIXTURE_Identifier(void) {
  RTIdentifier id = RTIdentifierCreate(0);
  REQUIRE(id != NULL);
  return id;
}

TEST_CreateRegisterSet_Valid(void) {
  RTValue *reg = CreateRegisterSet(1);
  REQUIRE(reg != NULL);
  ASSERT(reg[0] != NULL);
}

TEST_DeallocRegisterSet_Flat(void) {
  RTValue *reg = FIXTURE_RegisterSet(1);
  DeallocRegisterSet(reg, 1, FALSE);
}

TEST_DeallocRegisterSet_Recursive(void) {
  RTValue *reg = FIXTURE_RegisterSet(1);
  RTIdentifier id = FIXTURE_Identifier();
  RTValueSetIdentifier(reg[0], id);
  DeallocRegisterSet(reg, 1, TRUE);
}

int main(void) {

}

#endif
