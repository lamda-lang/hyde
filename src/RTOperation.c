#include "RTDecode.h"
#include "RTIdentifier.h"
#include "RTList.h"
#include "RTModule.h"
#include "RTOperation.h"
#include "RTString.h"
#include "RTValue.h"

RTValue RTOperationCreateIdentifier(RTByte **instruction) {
  RTInteger8Bit length = RTDecodeInteger8Bit(instruction);
  RTIdentifier id = RTIdentifierCreate(length);
  RTValue value = RTValueCreateIdentifier(id);
  if (value == NULL) {
    return NULL;
  }
  RTIdentifierDecode(id, instruction, length);
  return value;
}

RTValue RTOperationCreateString(RTByte **instruction) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTString string = RTStringCreate(length);
  RTValue value = RTValueCreateString(string);
  if (value == NULL) {
    return NULL;
  }
  RTStringDecode(string, instruction, length);
  return value;
}

RTValue RTOperationCreateList(RTByte **instruction) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTListCreate(length);
  RTValue value = RTValueCreateList(list);
  if (value == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTInteger32Bit elementIndex = RTDecodeVBRInteger32Bit(instruction);
    RTListSetRegisterIndexAtIndex(list, elementIndex, index);
  }
  return value;
}

RTValue RTOperationCreateModule(RTByte **instruction) {
  RTInteger32Bit capacity = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTModuleCreate(capacity);
  RTValue value = RTValueCreateModule(module);
  if (value == NULL) {
    return NULL;
  }
  for (RTIndex index = 0; index < capacity; index += 1) {
    RTInteger32Bit keyIndex = RTDecodeVBRInteger32Bit(instruction);
    RTInteger32Bit valueIndex = RTDecodeVBRInteger32Bit(instruction);
    RTModuleSetKeyValueIndexAtIndex(module, keyIndex, valueIndex, index);
  }
  return value;
}

void RTOperationFetchList(RTByte **instruction, RTValue *reg) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTValueGetList(reg[index]);
  RTListFetch(list, reg);
}

void RTOperationFetchModule(RTByte **instruction, RTValue *reg) {
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTValueGetModule(reg[index]);
  RTModuleFetch(module, reg);
}

#ifdef RT_OPERATION_TEST

#define LENGTH 8

int main(void) {

}

#endif
