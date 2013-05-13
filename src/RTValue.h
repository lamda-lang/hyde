#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

RTValue RTValueInit(RTType type, RTFlag mask);

RTType RTValueType(RTValue *value);

void RTValueSetFlag(RTValue *value, RTFlag mask, bool truth);

bool RTValueFlagSet(RTValue *value, RTFlag mask);

RTBoolean *RTValueBooleanBridge(RTValue *value);

RTIdentifier *RTValueIdentifierBridge(RTValue *value);

RTInteger *RTValueIntegerBridge(RTValue *value);

RTLambda *RTValueLambdaBridge(RTValue *value);

RTList *RTValueListBridge(RTValue *value);

RTMap *RTValueMapBridge(RTValue *value);

RTNil *RTValueNilBridge(RTValue *value);

RTString *RTValueStringBridge(RTValue *value);

void RTValueEnumerate(RTValue *value, RTBlock *block);

void RTValueDealloc(RTValue *value);

#endif
