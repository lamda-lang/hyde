#include "RTValue.h"

static inline RTValue Mask(RTFlag flag) {
  return (RTInteger64Bit)flag << 4 & 0XFF;
}

RTValue RTValueInit(RTType type) {
  return (RTValue)type;
}

RTValue RTValueMask(RTFlag flag, bool truth) {
  return truth ? Mask(flag) : 0;
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

void RTValueSetFlag(RTValue *value, RTFlag flag, bool truth) {
  RTValue mask = Mask(flag);
  *value = truth ? *value | mask : *value & ~mask;
}

bool RTValueFlagSet(RTValue *value, RTFlag flag) {
  RTValue mask = Mask(flag);
  return (*value & mask) == mask;
}

RTType RTValueType(RTValue *value) {
  return (RTType)(*value & 0XF);
}
