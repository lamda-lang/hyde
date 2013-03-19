#include "RTCreate.h"
#include "RTDecode.h"
#include "RTFetch.h"
#include "RTList.h"
#include "RTModule.h"
#include "RTPrimitive.h"

void RTFetchList(RTByte **instruction, RTPrimitive *reg) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTPrimitiveGetObject(reg[index]);
  RTListFetch(list, reg);
}

void RTFetchModule(RTByte **instruction, RTPrimitive *reg) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTPrimitiveGetObject(reg[index]);
  RTModuleFetch(module, reg);
}

#ifdef RT_FETCH_TEST

int main(void) {

}

#endif
