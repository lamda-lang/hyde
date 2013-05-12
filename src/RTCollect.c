#include "RTCollect.h"

static inline void EnumerateBlock(RTValue *value, RTBlock *block) {
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

void RTCollectValue(RTValue *value) {
  if (RTValueFlagSet(value, RTFlagMark)) {
    return;
  }
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

void RTCollectMarkValue(RTValue *value) {
  if (RTValueFlagSet(value, RTFlagMark)) {
    return;
  }
  RTValueSetFlag(value, RTFlagMark, true);
  EnumerateBlock(value, RTCollectMarkValue);
}

void RTCollectUnmarkValue(RTValue *value) {
  if (!RTValueFlagSet(value, RTFlagMark)) {
    return;
  }
  RTValueSetFlag(value, RTFlagMark, false);
  EnumerateBlock(value, RTCollectUnmarkValue);
}
