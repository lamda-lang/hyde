#include "RTValue.h"

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

void RTValueEnumerate(RTValue *value, RTBlock *block) {
  switch (RTValueType(value)) {
  case RTTypeLambda: {
      RTLambda *lambda = RTValueLambdaBridge(value);
      RTLambdaEnumerateContext(lambda, block);
      break;
    }
  case RTTypeList: {
      RTList *list = RTValueListBridge(value);
      RTListEnumerateValues(list, block);
      break;
    }
  case RTTypeMap: {
      RTMap *map = RTValueMapBridge(value);
      RTMapEnumerateKeys(map, block);
      RTMapEnumerateValues(map, block);
      break;
    }
  }
}

void RTValueDealloc(RTValue *value) {
  switch (RTValueType(value)) {
  case RTTypeBoolean: {
      RTBoolean *boolean = RTValueBooleanBridge(value);
      RTBooleanDealloc(boolean);
      break;
    }
  case RTTypeIdentifier: {
      RTIdentifier *id = RTValueIdentifierBridge(value);
      RTIdentifierDealloc(id);
      break;
    }
  case RTTypeLambda: {
      RTLambda *lambda = RTValueLambdaBridge(value);
      RTLambdaDealloc(lambda);
      break;
    }
  case RTTypeList: {
      RTList *list = RTValueListBridge(value);
      RTListDealloc(list);
      break;
    }
  case RTTypeMap: {
      RTMap *map = RTValueMapBridge(value);
      RTMapDealloc(map);
      break;
    }
  case RTTypeNil: {
      RTNil *nil = RTValueNilBridge(value);
      RTNilDealloc(nil);
      break;
    }
  case RTTypeString: {
      RTString *string = RTValueStringBridge(value);
      RTStringDealloc(string);
      break;
    }
  }
}
