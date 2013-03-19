#include "RTCreate.h"
#include "RTDecode.h"
#include "RTExecute.h"
#include "RTFetch.h"

static RTCreate create[] = {
  [0] = RTCreateIdentifier,
  [1] = RTCreateList,
  [2] = RTCreateModule,
  [3] = RTCreateString
};

static RTFetch fetch[] = {
  [0] = RTFetchList,
  [1] = RTFetchModule
};

RTPrimitive RTExecuteBytecode(RTByte *code, RTPrimitive *reg) {
  RTInteger32Bit createCount = RTDecodeVBRInteger32Bit(&code);
  for (RTIndex index = 0; index < createCount; index += 1) {
    RTInteger8Bit opcode = RTDecodeInteger8Bit(&code);
    RTPrimitive primitive = create[opcode](&code);
    if (primitive == NULL) {
      return NULL;
    }
    reg[index] = primitive;
  }
  RTInteger32Bit fetchCount = RTDecodeVBRInteger32Bit(&code);
  for (RTIndex index = 0; index < fetchCount; index += 1) {
    RTInteger8Bit opcode = RTDecodeInteger8Bit(&code);
    fetch[opcode](&code, reg);
  }
  return reg[0];
}

#ifdef RT_EXECUTE_TEST

int main(void) {

}

#endif
