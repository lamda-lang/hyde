#include "RTDecode.h"
#include "RTExecute.h"
#include "RTMemory.h"
#include "RTValue.h"

typedef enum {
  CREATE_IDENTIFIER = 0,
  CREATE_LIST = 1,
  CREATE_MODULE = 2,
  CREATE_STRING = 3
} RTOpcode;

static inline void DeallocRegisterSet(RTValue *reg, RTInteger32Bit count, RTBool recursive) {
  for (RTIndex index = 0; index < count; index += 1) {
    RTValueDealloc(reg[index], recursive);
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
      DeallocRegisterSet(reg, index, FALSE);
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
    /* missing */
  }
  RTValue result = reg[0];
  RTMemoryDealloc(reg);
  return result;
}

#ifdef RT_EXECUTE_TEST

int main(void) {

}

#endif
