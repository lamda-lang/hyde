#include "RTOperation.h"

static inline RTBool CreateIdentifier(RTByte **instruction, RTValue *reg, RTInteger32Bit index) {
  RTInteger8Bit length = RTDecodeInteger8Bit(instruction);
  RTIdentifier id = RTIdentifierCreate(length);
  if (id == NULL) {
    return FALSE;
  }
  RTIdentifierDecode(id, instruction, length);
  RTValueSetIdentifier(reg[index], id);
  return TRUE;
}

static inline RTBool CreateList(RTByte **instruction, RTValue *reg, RTInteger32Bit index) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTListCreate(length);
  if (list == NULL) {
    return FALSE;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTValue value = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTListSetValueAtIndex(list, value, index);
  }
  RTValueSetList(reg[index], list);
  return TRUE;
}

static inline RTBool CreateModule(RTByte **instruction, RTValue *reg, RTInteger32Bit index) {
  RTInteger32Bit capacity = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTModuleCreate(capacity);
  if (module == NULL) {
    return FALSE;
  }
  for (RTIndex index = 0; index < capacity; index += 1) {
    RTValue key = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTValue value = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTModuleSetValueForKey(module, value, key);
  }
  RTValueSetModule(reg[index], module);
  return TRUE;
}

static inline RTBool CreateString(RTByte **instruction, RTValue *reg, RTInteger32Bit index) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTString string = RTStringCreate(length);
  if (string == NULL) {
    return FALSE;
  }
  RTStringDecode(string, instruction, length);
  RTValueSetString(reg[index], string);
  return TRUE;
}

RTBool ExecuteInstruction(RTByte **instruction, RTValue *reg, RTInteger32Bit index) {
  RTInteger8Bit opcode = RTDecodeInteger8Bit(instruction);
  switch (opcode) {
  case CREATE_IDENTIFIER:
    return CreateIdentifier(instruction, reg, index);
  case CREATE_LIST:
    return CreateList(instruction, reg, index);
  case CREATE_MODULE:
    return CreateModule(instruction, reg, index);
  case CREATE_STRING:
    return CreateString(instruction, reg, index);
  }
}

#ifdef RT_OPERATION_TEST

int main(void) {

}

#endif
