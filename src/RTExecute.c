#include "RTDecode.h"
#include "RTExecute.h"
#include "RTOperation.h"

static RTCreate create[] = {
  [0] = RTOperationCreateIdentifier,
  [1] = RTOperationCreateList,
  [2] = RTOperationCreateModule,
  [3] = RTOperationCreateString
};

static RTFetch fetch[] = {
  [0] = RTOperationFetchList,
  [1] = RTOperationFetchModule
};

RTValue RTExecuteBytecode(RTByte *code, RTValue *reg) {
  RTInteger32Bit createCount = RTDecodeVBRInteger32Bit(&code);
  for (RTIndex index = 0; index < createCount; index += 1) {
    RTInteger8Bit opcode = RTDecodeInteger8Bit(&code);
    RTValue primitive = create[opcode](&code);
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
