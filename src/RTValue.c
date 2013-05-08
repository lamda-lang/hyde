#include "RTValue.h"

RTBoolean RTValueBooleanBridge(RTValue value) {
  return RTValueGetType(value) ==  RTTypeBoolean ? (RTBoolean)value : NULL;
}

RTIdentifier RTValueIdentifierBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeIdentifier ? (RTIdentifier)value : NULL;
}

RTInteger RTValueIntegerBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeInteger ? (RTInteger)value : NULL;
}

RTLambda RTValueLambdaBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeLambda ? (RTLambda)value : NULL;
}

RTList RTValueListBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeList ? (RTList)value : NULL;
}

RTMap RTValueMapBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeMap ? (RTMap)value : NULL;
}

RTNil RTValueNilBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeNil ? (RTNil)value : NULL;
}

RTString RTValueStringBridge(RTValue value) {
  return RTValueGetType(value) == RTTypeString ? (RTString)value : NULL;
}

void RTValueSetFlag(RTValue value, RTFlag flag, RTBool set) {
  *value = RTBaseSetFlag(*value, flag, set);
}

RTBool RTValueFlagSet(RTValue value, RTFlag flag) {
  return RTBaseFlagSet(*value, flag);
}

RTType RTValueGetType(RTValue value) {
  return RTBaseGetType(*value);
}
