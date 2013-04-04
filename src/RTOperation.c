#include "RTOperation.h"

typedef enum {
  CREATE_IDENTIFIER = 0,
  CREATE_INTEGER = 1,
  CREATE_LIST = 2,
  CREATE_MODULE = 3,
  CREATE_STRING = 4
} RTOpcode;

static inline RTBool CreateIdentifier(RTByte **instruction, RTValue *reg) {
  RTIdentifier id = RTIdentifierDecode(instruction);
  if (id == NULL) {
    return FALSE;
  }
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTValueSetIdentifier(reg[index], id);
  return TRUE;
}

static inline RTBool CreateInteger(RTByte **instruction, RTValue *reg) {
  RTInteger64Bit value = RTDecodeInteger64Bit(instruction);
  RTInteger integer = RTIntegerCreate64Bit(value);
  if (integer == NULL) {
    return FALSE;
  }
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTValueSetInteger(reg[index], integer);
  return TRUE;
}

static inline RTBool CreateList(RTByte **instruction, RTValue *reg) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(instruction);
  RTList list = RTListCreate(length);
  if (list == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    RTValue value = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTListSetValueAtIndex(list, value, index);
  }
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTValueSetList(reg[index], list);
  return TRUE;
}

static inline RTBool CreateModule(RTByte **instruction, RTValue *reg) {
  RTInteger32Bit capacity = RTDecodeVBRInteger32Bit(instruction);
  RTModule module = RTModuleCreate(capacity);
  if (module == NULL) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < capacity; index += 1) {
    RTValue key = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTValue value = reg[RTDecodeVBRInteger32Bit(instruction)];
    RTModuleSetValueForKey(module, value, key);
  }
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTValueSetModule(reg[index], module);
  return TRUE;
}

static inline RTBool CreateString(RTByte **instruction, RTValue *reg) {
  RTString string = RTStringDecode(instruction);
  if (string == NULL) {
    return FALSE;
  }
  RTInteger32Bit index = RTDecodeVBRInteger32Bit(instruction);
  RTValueSetString(reg[index], string);
  return TRUE;
}

RTBool RTOperationExecute(RTByte **instruction, RTValue *reg) {
  RTOpcode opcode = RTDecodeInteger8Bit(instruction);
  switch (opcode) {
  case CREATE_IDENTIFIER:
    return CreateIdentifier(instruction, reg);
  case CREATE_INTEGER:
    return CreateInteger(instruction, reg);
  case CREATE_LIST:
    return CreateList(instruction, reg);
  case CREATE_MODULE:
    return CreateModule(instruction, reg);
  case CREATE_STRING:
    return CreateString(instruction, reg);
  }
}

#ifdef RT_OPERATION_TEST

int main(void) {

}

#endif
