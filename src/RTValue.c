#include "RTValue.h"

typedef struct {
  RTDealloc *dealloc;
  RTHash *hash;
  RTEnumerate *enumerate;
} RTClass;

RTClass class[] = {
  [RTTypeBoolean] = {
    .dealloc = RTBooleanDealloc,
    .hash = RTBooleanHash
  },
  [RTTypeIdentifier] = {
    .dealloc = RTIdentifierDealloc,
    .hash = RTIdentifierHash
  },
  [RTTypeInteger] = {
    .dealloc = RTIntegerDealloc,
    .hash = RTIntegerHash
  },
  [RTTypeLambda] = {
    .dealloc = RTLambdaDealloc,
    .hash = RTLambdaHash,
    .enumerate = RTLambdaEnumerate
  },
  [RTTypeList] = {
    .dealloc = RTListDealloc,
    .hash = RTListHash,
    .enumerate = RTListEnumerate
  },
  [RTTypeMap] = {
    .dealloc = RTMapDealloc,
    .hash = RTMapHash,
    .enumerate = RTMapEnumerate
  },
  [RTTypeNil] = {
    .dealloc = RTNilDealloc,
    .hash = RTNilHash
  },
  [RTTypeString] = {
    .dealloc = RTStringDealloc,
    .hash = RTStringHash
  }
};

RTValue RTValueInit(RTType type, RTFlag mask) {
  return type | mask;
}

RTType RTValueType(RTValue *value) {
  return *value & 0XF;
}

void RTValueSetFlag(RTValue *value, RTFlag mask, bool truth) {
  *value = truth ? *value | mask : *value & ~mask;
}

bool RTValueFlagSet(RTValue *value, RTFlag mask) {
  return (*value & mask) == mask;
}

bool RTValueBaseFlagSet(RTValue value, RTFlag mask) {
  return (value & mask) == mask;
}

RTBoolean *RTValueBooleanBridge(RTValue *value) {
  return (RTBoolean *)value;
}

RTIdentifier *RTValueIdentifierBridge(RTValue *value) {
  return (RTIdentifier *)value;
}

RTInteger *RTValueIntegerBridge(RTValue *value) {
  return (RTInteger *)value;
}

RTLambda *RTValueLambdaBridge(RTValue *value) {
  return (RTLambda *)value;
}

RTList *RTValueListBridge(RTValue *value) {
  return (RTList *)value;
}

RTMap *RTValueMapBridge(RTValue *value) {
  return (RTMap *)value;
}

RTNil *RTValueNilBridge(RTValue *value) {
  return (RTNil *)value;
}

RTString *RTValueStringBridge(RTValue *value) {
  return (RTString *)value;
}

void RTValueEnumerate(RTValue *value, void (*block)(RTValue *value)) {
  RTType type = RTValueType(value);
  RTEnumerate *enumerate = class[type].enumerate;
  if (enumerate != NULL) {
    enumerate(value, block);
  }
}

void RTValueDealloc(RTValue *value) {
  RTType type = RTValueType(value);
  RTDealloc *dealloc = class[type].dealloc;
  if (dealloc != NULL) {
    dealloc(value);
  }
}

RTInteger64Bit RTValueHash(RTValue *value) {
  RTType type = RTValueType(value);
  return class[type].hash(value);
}
