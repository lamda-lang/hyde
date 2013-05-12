#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

RTValue RTValueInit(RTType type);

RTValue RTValueMask(RTFlag flag, bool truth);

RTBoolean *RTValueBooleanBridge(RTValue *value);

RTIdentifier *RTValueIdentifierBridge(RTValue *value);

RTInteger *RTValueIntegerBridge(RTValue *value);

RTLambda *RTValueLambdaBridge(RTValue *value);

RTList *RTValueListBridge(RTValue *value);

RTMap *RTValueMapBridge(RTValue *value);

RTNil *RTValueNilBridge(RTValue *value);

RTString *RTValueStringBridge(RTValue *value);

void RTValueSetFlag(RTValue *value, RTFlag flag, bool truth);

bool RTValueFlagSet(RTValue *value, RTFlag flag);

RTType RTValueType(RTValue *value);

#endif
