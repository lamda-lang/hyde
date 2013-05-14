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

bool RTValueEqual(RTValue *value, RTValue *other) {
  RTType type = RTValueType(value);
  if (type != RTValueType(other)) return false;
  switch (type) {
  case RTTypeBoolean: {
      RTBoolean *boolean = RTValueBooleanBridge(value);
      RTBoolean *second = RTValueBooleanBridge(other);
      return RTBooleanEqual(boolean, second);
    }
  case RTTypeIdentifier: {
      RTIdentifier *id = RTValueIdentifierBridge(value);
      RTIdentifier *second = RTValueIdentifierBridge(other);
      return RTIdentifierEqual(id, second);
    }
  case RTTypeInteger: {
      RTInteger *integer = RTValueIntegerBridge(value);
      RTInteger *second = RTValueIntegerBridge(other);
      return RTIntegerEqual(integer, second);
    }
  case RTTypeLambda: {
      RTLambda *lambda = RTValueLambdaBridge(value);
      RTLambda *second = RTValueLambdaBridge(other);
      return RTLambdaEqual(lambda, second);
    }
  case RTTypeList: {
      RTList *list = RTValueListBridge(value);
      RTList *second = RTValueListBridge(other);
      return RTListEqual(list, second);
    }
  case RTTypeMap: {
      RTMap *map = RTValueMapBridge(value);
      RTMap *second = RTValueMapBridge(other);
      return RTMapEqual(map, second);
    }
  case RTTypeNil: {
      return true;
    }
  case RTTypeString: {
      RTString *string = RTValueStringBridge(value);
      RTString *second = RTValueStringBridge(other);
      return RTStringEqual(string, second);
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
  case RTTypeInteger: {
      RTInteger *integer = RTValueIntegerBridge(value);
      RTIntegerDealloc(integer);
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

RTInteger64Bit RTValueHash(RTValue *value) {
  switch (RTValueType(value)) {
  case RTTypeBoolean: {
      RTBoolean *boolean = RTValueBooleanBridge(value);
      return RTBooleanHash(boolean);
    }
  case RTTypeIdentifier: {
      RTIdentifier *id = RTValueIdentifierBridge(value);
      return RTIdentifierHash(id);
    }
  case RTTypeInteger: {
      RTInteger *integer = RTValueIntegerBridge(value);
      return RTIntegerHash(integer);
    }
  case RTTypeLambda: {
      RTLambda *lambda = RTValueLambdaBridge(value);
      return RTLambdaHash(lambda);
    }
  case RTTypeList: {
      RTList *list = RTValueListBridge(value);
      return RTListHash(list);
    }
  case RTTypeMap: {
      RTMap *map = RTValueMapBridge(value);
      return RTMapHash(map);
    }
  case RTTypeNil: {
      return 0;
    }
  case RTTypeString: {
      RTString *string = RTValueStringBridge(value);
      return RTStringHash(string);
    }
  }
}
