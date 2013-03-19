#include "RTCreate.h"
#include "RTDecode.h"
#include "RTIdentifier.h"
#include "RTList.h"
#include "RTModule.h"
#include "RTPrimitive.h"
#include "RTString.h"

RTPrimitive RTCreateIdentifier(RTByte **instruction) {
  RTInteger8Bit length = RTDecodeInteger8Bit(instruction);
  RTIdentifier id = RTIdentifierCreate(length);
  RTPrimitive primitive = RTPrimitiveCreate(id, IDENTIFIER);
  if (primitive == NULL) {
    return NULL;
  }
  RTIdentifierDecode(id, instruction, length);
  return primitive;
}

RTPrimitive RTCreateString(RTByte **instruction) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTString string = RTStringCreate(length);
  RTPrimitive primitive = RTPrimitiveCreate(string, STRING);
  if (primitive == NULL) {
    return NULL;
  }
  RTStringDecode(string, instruction, length);
  return primitive;
}

RTPrimitive RTCreateList(RTByte **instruction) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTListCreate(length);
  RTPrimitive primitive = RTPrimitiveCreate(list, LIST);
  if (primitive == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTInteger32Bit elementIndex = RTDecodeVBRInteger32Bit(instruction);
    RTListSetRegisterIndexAtIndex(list, elementIndex, index);
  }
  return primitive;
}

RTPrimitive RTCreateModule(RTByte **instruction) {
  RTInteger32Bit capacity = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTModuleCreate(capacity);
  RTPrimitive primitive = RTPrimitiveCreate(module, MODULE);
  if (primitive == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < capacity; index += 1) {
    RTInteger32Bit keyIndex = RTDecodeVBRInteger32Bit(instruction);
    RTInteger32Bit valueIndex = RTDecodeVBRInteger32Bit(instruction);
    RTModuleSetKeyValueIndexAtIndex(module, keyIndex, valueIndex, index);
  }
  return primitive;
}

#ifdef RT_CREATE_TEST

#define LENGTH 8

int main(void) {

}

#endif
