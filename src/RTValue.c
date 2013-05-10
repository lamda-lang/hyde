#include "RTValue.h"

RTValue RTValueInit(RTType type, RTImplementation implementation, RTFlag mask) {
  return type | implementation | mask;
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
  *value = truth ? *value | flag : *value & ~flag;
}

bool RTValueFlagSet(RTValue *value, RTFlag flag) {
  return (*value & flag) == flag;
}

RTType RTValueType(RTValue *value) {
  return *value & 0XF;
}

RTImplementation RTValueImplementation(RTValue *value) {
  return *value & 0X30;
}
